//----------------------------------------------------
//Copyright (C), 2004-2009,  lst.
//��Ȩ���� (C), 2004-2009,   lst.
//����ģ��:flash�ļ�ϵͳ
//���ߣ�lst
//�汾��V1.0.0
//�ļ�����:djyfs��windows�ļ�ϵͳ�����ӿڣ�
//����˵��:
//�޶���ʷ:
//2. ...
//1. ����: 2009-01-04
//   ����: lst
//   �°汾��: V1.0.0
//   �޸�˵��: ԭʼ�汾
//------------------------------------------------------

#include "os_inc.h"     

#if (cfg_djyfs == 1) && (cfg_run_mode != cn_mode_tiny))

#include "file.h"
#include "windows.h"

//----�ƶ��ļ���ָ��-----------------------------------------------------------
//����: ��һ���ļ��Ķ�ָ���ƶ���һ����λ��
//����: DBX_flash_tag����������flash�ļ���Ĵ洢ý���ǩ
//      fp��Ŀ���ļ�ָ��
//      new_ptr���µĶ�ָ��
//����: true=�ɹ���false=�д���
//-----------------------------------------------------------------------------
bool_t __DFFSD_move_file_read_ptr(struct st_DBX_flash_tag *DBX_flash_tag,
                            djyfs_file *fp,sint64_t new_ptr)
{
    if(new_ptr > fp->file_size)
        return false;

    switch (fp->open_mode)
    {
        case enum_r_rb:
        {
            fp->read_ptr = new_ptr;             //��λ��
        }break;
        case enum_w_wb:
        {
            return false;                       //��λ����Ч
        }break;
        case enum_a_ab:
        {
            return false;                       //��λ����Ч
        }break;
        case enum_r_rb_plus:
        {
            fp->read_ptr = new_ptr;             //��λ��
            fp->write_ptr = new_ptr;            //дλ��
        }break;
        case enum_w_wb_plus:
        {
            fp->read_ptr = new_ptr;             //��λ��
            fp->write_ptr = new_ptr;            //дλ��
        }break;
        case enum_a_ab_plus:
        {
            fp->read_ptr = new_ptr;             //��λ��
        }break;
        default: return false;
    }
    return true;
}

//----�ƶ��ļ�дָ��-----------------------------------------------------------
//����: ��һ���ļ���дָ���ƶ���һ����λ��
//����: DBX_flash_tag����������flash�ļ���Ĵ洢ý���ǩ
//      fp��Ŀ���ļ�ָ��
//      new_ptr���µ�дָ��
//����: true=�ɹ���false=�д���
//-----------------------------------------------------------------------------
bool_t __DFFSD_move_file_write_ptr(struct st_DBX_flash_tag *DBX_flash_tag,
                             djyfs_file *fp,sint64_t new_ptr)
{
    switch (fp->open_mode)
    {
        case enum_r_rb:
        {
            return false;                       //ֻ���ļ���дλ����Ч
        }break;
        case enum_w_wb:
        {
            fp->write_ptr = new_ptr;            //дλ��
        }break;
        case enum_a_ab:
        {
            fp->write_ptr = new_ptr;            //дλ��
        }break;
        case enum_r_rb_plus:
        {
            fp->read_ptr = new_ptr;             //��λ��
            fp->write_ptr = new_ptr;            //дλ��
        }break;
        case enum_w_wb_plus:
        {
            fp->read_ptr = new_ptr;             //��λ��
            fp->write_ptr = new_ptr;            //дλ��
        }break;
        case enum_a_ab_plus:
        {
            fp->write_ptr = new_ptr;            //дλ��
        }break;
        default: return false;
    }
    if(new_ptr > fp->file_size)       //дָ�볬���ļ�����
    {
        //��FDT�����޸��ļ�����
       __DFFSD_update_FDT_file_size(DBX_flash_tag,fp,fp->write_ptr);
        fp->file_size = fp->write_ptr;  //��дָ�븲���ļ�����
    }
    return true;
}


//----д��flash�ļ�------------------------------------------------------------
//���ܣ��ѻ������е�����д���ļ���ִ�����в�����
//      1�����д���������㹻�Ŀռ䣬������д��д���������ɡ�
//      2�����д������û���㹻�Ŀռ䣬��ͬд������ԭ�����ݺ����뻺�����е�����
//         һ��д��flash
//      3��д����ɺ�����������Ƿ���Ҫͬ����ִ��֮��
//      4�����FDT���DDR���Ƿ���Ҫ�޸Ĳ�ִ��֮
//������buf�����뻺����
//      len������д���������
//      fp�����������ļ�ָ��
//���أ�����д�����������������д��������ԭ�е�����
//ע:   ��������û���ȵ���__DFFSD_write_buf_to_flash��������дbuf�е����ݣ�����
//      ������Ҫ��һ�ε���flashд������Ч�ʵͣ����ǰ�д��������������buf�е�����
//      �ϲ�һ��д��flash.
//-----------------------------------------------------------------------------
uint32_t DFFSD_write_file(struct file_rsc *fp,uint8_t *buf,uint32_t len)
{
    struct flash_chip *chip;
    struct st_DBX_device_tag *DBX_device_tag;
    struct st_DBX_flash_tag *DBX_flash_tag;
    struct file_access_tag access_tag;
    uint32_t completed = 0,write_len,write_sum;
    sint64_t wr_point;
    uint32_t offset_start;
    uint32_t block_no,start_block,end_block,loop,temp;
    uint32_t true_block,last_block;
    uint32_t buffed_data,spare_len; //�ļ�д�������е���������ʣ��������
   
    if((fp==NULL)||(len==0)||(buf==NULL))
        return 0;
    DBX_device_tag = (struct st_DBX_device_tag *)(fp->home_DBX->private_tag);
    //�ļ���ָ��
    DBX_flash_tag = (struct st_DBX_flash_tag *)DBX_device_tag->DBX_medium_tag;
    chip = DBX_flash_tag->chip;     //ȡ�ļ���(�ļ�)����оƬ
    buffed_data = ring_check(fp->p_write_buf); //��黺�����е�������
    if(ring_capacity(fp->p_write_buf) - buffed_data >= len)
    {//�����������㹻��������ֱ�Ӱ�����д�����������ɡ�
            completed = ring_write(fp->p_write_buf,(uint8_t*)buf,len);

            completed+=buffed_data;       
    }
    else
    {
        //���������û���㹻����������ѱ�����Ҫд���������ͬ������ԭ��������
        //һ��д��flash�����濪ʼִ��д�������
        //�������������е�������һ��һ��Ҫд��flash��������
        write_sum = len + buffed_data;
        spare_len = buffed_data;        //������ʣ��������
        wr_point = fp->write_ptr - buffed_data;
        //������ʼдλ�ô����ļ��ڵڼ����ƫ����
        start_block = (u32)(wr_point /chip->block_size);
        offset_start = (u32)(wr_point % chip->block_size);
        //������ֹдλ�ô����ļ��ڵڼ���
        end_block = (u32)((fp->write_ptr + len -1)/chip->block_size);
        __DFFSD_get_access_info(DBX_flash_tag,fp,&access_tag);
        //��λд���Ŀ�ţ��ļ����ڵ���Կ�š�
        block_no = access_tag.write_block_no;
        last_block = access_tag.last_block_no;
        for(loop = start_block; loop <= end_block; loop++)
        {
            if(((wr_point >= access_tag.true_size) && (wr_point != 0)))
            {
                //����һ���¿�
                block_no = __DFFSD_allocate_block(DBX_flash_tag);
                if(block_no == cn_limit_uint32) //����ʧ��(�޿��п�)
                    break;
            }
            //���㱾��д������ݳ���
            if(write_sum - completed > chip->block_size - offset_start)
                write_len = chip->block_size - offset_start;
            else
                write_len = write_sum - completed;
            if(spare_len != 0)  //д�������ﻹ������
            {
                temp = ring_read(fp->p_write_buf,
                                 chip->block_buf+offset_start,write_len);
                spare_len -= temp;  //д��������ȥʵ�ʶ�����������
                //ʵ�ʶ�������������write_len�٣�˵�����ζ��Ѿ���д���������ա�
                if(temp != write_len)
                {
                    //���������뻺�����п�������
                    memcpy(chip->block_buf+temp+offset_start,
                                buf,write_len-temp);
                }
            }else   //д�������Ѿ��գ������뻺������������
                memcpy(chip->block_buf+offset_start,
                                       buf+completed-buffed_data,write_len);
            if(wr_point >= access_tag.true_size)    //׷������
            {
                if(offset_start == 0)   //��д��Ŀ���������Ч����
                {
                    //д��Ŀ���
                    true_block = __DFFSD_write_new_block(DBX_flash_tag,block_no,
                                                            0,write_len);
                    if(true_block != cn_limit_uint32)
                    {//��ȷд��
                        if(wr_point != 0)
                            __DFFSD_add_MAT_item(DBX_flash_tag,last_block,true_block);
                    }else       //д�����
                        break;
                }else                   //����׷�ӣ�����д��Ŀ��Ѿ��в�����Ч����
                {
                    //д��Ŀ���
                    true_block = __DFFSD_write_append_block(DBX_flash_tag,block_no,
                                                    offset_start,write_len);
                    if(true_block != cn_limit_uint32)
                    {//��ȷд��
                        if(true_block != block_no)   //д��ʱ�����˿��滻
                            __DFFSD_update_MAT_item(DBX_flash_tag,block_no,true_block);
                    }else       //д�����
                        break;
                }
                last_block = true_block;
                access_tag.true_size += write_len;
                wr_point += write_len;
                chip->erase_block(DBX_flash_tag->PCRB_no
                                  + DBX_flash_tag->start_block);
            }else   //���ļ����м�д�룬�����������Ҫʹ��PCRB����б���
            {
                //д��Ŀ���
                true_block = __DFFSD_write_update_block(DBX_flash_tag,block_no,
                                                offset_start,write_len);
                if(true_block != cn_limit_uint32)
                {//��ȷд��
                    if(true_block != block_no)   //д��ʱ�����˿��滻
                        __DFFSD_update_MAT_item(DBX_flash_tag,block_no,true_block);
                }else       //д�����
                    break;
                //ȷ����һѭ��д���Ŀ�ţ��ļ����ڵ���Կ�š�
                block_no = DBX_flash_tag->DDR_MAT[block_no].next;
                wr_point += write_len;
                if(wr_point > access_tag.true_size)
                    access_tag.true_size = wr_point;
                chip->erase_block(DBX_flash_tag->PCRB_no
                                  + DBX_flash_tag->start_block);
            }
            completed += write_len;
            offset_start = 0;   //�ڶ��鿪ʼ����ʼƫ�Ƶ�ַ�϶���0
        }
    }
    if((completed - buffed_data) > 0)      //д��������
    {
        __DFFSD_sync_buf_after_write(DBX_flash_tag,fp,completed-buffed_data);
        __DFFSD_move_file_write_ptr(DBX_flash_tag,fp,
                                    fp->write_ptr + completed-buffed_data);
    }
    __DFFSD_write_DDR(DBX_flash_tag);//���DDR���б仯��д��flash��
    return completed - buffed_data;
}
//���ܣ����ļ��е����ݶ��뵽�������У�ִ�����²���
//      1����������������û�����ݣ�������뵽���ջ�������
//      2�������������е������������û�����ݣ����flash�в����ȡ�������ղ�Խ��
//         �߽�Ϊ������޶ȵ���д��������
//      3��������ɺ��Ƿ���Ҫͬ��д��������ִ��֮
//������buf�����뻺����
//      len��������������
//      fp�����������ļ�ָ��
//���أ�ʵ�ʶ�ȡ���ֽ���
//-----------------------------------------------------------------------------
uint32_t DFFSD_read_file(struct file_rsc *fp,uint8_t *buf,uint32_t len)
{
    struct flash_chip *chip;
    struct st_DBX_device_tag *DBX_device_tag;
    struct st_DBX_flash_tag *DBX_flash_tag;
    uint32_t completed = 0,read_len,result_len;
    uint32_t offset_start;
    uint32_t block_no,start_block,end_block,loop;
    uint32_t read_result;
    if((fp==NULL)||(len==0)||(buf==NULL))
        return 0;
    DBX_device_tag = (struct st_DBX_device_tag *)(fp->home_DBX->private_tag);
    //�ļ���ָ��
    DBX_flash_tag = (struct st_DBX_flash_tag *)DBX_device_tag->DBX_medium_tag;
    __DFFSD_sync_buf_before_read(DBX_flash_tag,fp,len);
    chip = DBX_flash_tag->chip;     //ȡ�ļ���(�ļ�)����оƬ
    //������ʼ��дλ�ô����ļ��ڵڼ���
    start_block = (u32)(fp->read_ptr/chip->block_size);
    //������ֹ��дλ�ô����ļ��ڵڼ���
    end_block = (u32)((fp->read_ptr + len -1)/chip->block_size);
    offset_start = fp->read_ptr % chip->block_size;
    if(fp->read_ptr + len >fp->file_size)
        result_len = (u32)(fp->file_size - fp->read_ptr);
    else
        result_len = len;
    //��λ������Ŀ�ţ��ļ����ڵ���Կ�š�
    block_no = __DFFSD_locate_block(DBX_flash_tag,fp,fp->read_ptr);
    for(loop = start_block; loop <= end_block; loop++)
    {
        if(result_len - completed > chip->block_size - offset_start)
            read_len = chip->block_size - offset_start;
        else
            read_len = result_len - completed;
        //����Ŀ���
        read_result =chip->read_data_with_ecc(
                                block_no + DBX_flash_tag->start_block,
                                offset_start,buf+completed,read_len);
        if(read_result == 2)    //�������󣬻���
        {
            return completed;
        }
        completed += read_len;
        offset_start = 0;   //�ڶ��鿪ʼ����ʼƫ�Ƶ�ַ�϶���0
        block_no = DBX_flash_tag->DDR_MAT[block_no].next;
    }
    fp->read_ptr += completed;
    return completed;
}

//----ˢд������---------------------------------------------------------------
//����: ���ļ�д������������д��flash
//������fp�����������ļ�ָ��
//���أ�ʵ��д��flash���ֽ���
//-----------------------------------------------------------------------------
uint32_t DFFSD_flush_file(struct file_rsc *fp)
{
    struct st_DBX_device_tag *DBX_device_tag;
    struct st_DBX_flash_tag *DBX_flash_tag;
    if(fp==NULL)
        return 0;
    DBX_device_tag = (struct st_DBX_device_tag *)(fp->home_DBX->private_tag);
    //�ļ���ָ��
    DBX_flash_tag = (struct st_DBX_flash_tag *)DBX_device_tag->DBX_medium_tag;
    return __DFFSD_write_buf_to_flash(DBX_flash_tag,fp);
}

//----��ѯ�ļ��ɶ�������-------------------------------------------------------
//���ܣ���ѯһ���ļ����ж��ٿɶ����ݣ����ڹ�̬�ļ�����flash�ļ�����˵�������ļ�
//      ����-��ǰָ�룬�����ı�׼���岢��һ����ˣ�����ͨ�Ŷ��ӡ����ң��ļ���д
//      ָ����α�ʾ������ļ�ϵͳ������ʵ���йأ��ļ�ϵͳ�ĺ��ĳ���Ӧ�����κ�
//      ���衣
//������fp�����������ļ�ָ��
//���أ��ļ��ɶ����ݵ��ֽ���
//-----------------------------------------------------------------------------
sint64_t DFFSD_query_file_stocks(struct file_rsc *fp)
{
    struct st_DBX_device_tag *DBX_device_tag;
    struct st_DBX_flash_tag *DBX_flash_tag;
    struct fdt_info FDT_item;
    
    if(fp == NULL)
        return 0;
    DBX_device_tag = (struct st_DBX_device_tag *)(fp->home_DBX->private_tag);
    DBX_flash_tag = (struct st_DBX_flash_tag*)DBX_device_tag->DBX_medium_tag;
    __DFFSD_read_FDT_item(DBX_flash_tag,
                          (uint32_t)fp->file_medium_tag,&FDT_item);
    if(FDT_item.mattr & cn_FS_ATTR_DIRECTORY)
        return 0;       //Ŀ¼���ܶ�
    return fp->file_size - fp->read_ptr;
}


//----��ѯ�ļ���д������-------------------------------------------------------
//���ܣ���ѯһ���ļ�����д��������ݣ����ڹ�̬�ļ�����flash�ļ��������ܾ����ļ�
//      ���ʣ��ռ䣬�����ı�׼���岢��һ����ˣ�����ͨ�Ŷ��ӡ����ң��ļ���ʣ��
//      �ռ���α�ʾ������ļ�ϵͳ������ʵ���йأ��ļ�ϵͳ�ĺ��ĳ���Ӧ�����κ�
//      ���衣������ΪDBX_flash_tag->free_sum�����ļ��Կ�д�����������
//      flash�ļ�ϵͳ�ļ��㷽ʽ��:
//      1���ļ��ѷ���Ŀ������-�ļ��ߴ硣
//      2�������ļ���ʣ��ռ�DBX_flash_tag->free_sum��
//      3����ȥ�ļ������������е�������
//������fp�����������ļ�ָ��
//���أ��ļ�����д����ֽ���
//-----------------------------------------------------------------------------
sint64_t DFFSD_query_file_cubage(struct file_rsc *fp)
{
    struct st_DBX_device_tag *DBX_device_tag;
    struct st_DBX_flash_tag *DBX_flash_tag;
    struct flash_chip *chip;
    struct fdt_info FDT_item;
    if(fp == NULL)
        return 0;
    DBX_device_tag = (struct st_DBX_device_tag *)(fp->home_DBX->private_tag);
    DBX_flash_tag = (struct st_DBX_flash_tag*)DBX_device_tag->DBX_medium_tag;
    chip = DBX_flash_tag->chip;
    __DFFSD_read_FDT_item(DBX_flash_tag,
                          (uint32_t)fp->file_medium_tag,&FDT_item);
    if((FDT_item.mattr & cn_FS_ATTR_READ_ONLY)
                || (FDT_item.mattr & cn_FS_ATTR_DIRECTORY))
        return 0;       //ֻ���ļ���Ŀ¼����д��

    return DBX_flash_tag->free_sum * chip->block_size;  // - buffed_size + size;
}

//----�����ļ�����-------------------------------------------------------------
//���ܣ������ļ����ȣ�����ʵ�ʳ��Ƚ���β������ʵ�ʳ��Ƚ�׷�ӿռ䡣����������Ҫ
//      ������������ʽд������֮ǰ��Ԥ�ȷ���洢����
//������fp�����������ļ�ָ��
//      new_size���µ��ļ����ȡ�
//���أ��µ��ļ����ȣ�����new_size�������ȣ�һ������Ϊ�ļ���û���㹻����������
//-----------------------------------------------------------------------------
sint64_t __DFFSD_set_file_size(struct file_rsc *fp,sint64_t new_size)
{
    struct st_DBX_device_tag *DBX_device_tag;
    sint64_t result,temp;
    uint32_t origin_blocks,new_blocks,last_block_no,next_block_no;
    uint32_t loop;
    struct st_DBX_flash_tag *DBX_flash_tag;
    struct flash_chip *chip;
    struct fdt_info FDT_item;
    //����Ŀ¼��FDT_item
    if(fp == NULL)
        return 0;
    if(new_size == fp->file_size)
        return new_size;    //�µ��ļ�������ԭ������ȣ�ֱ�ӷ��ء�
    DBX_device_tag = (struct st_DBX_device_tag *)(fp->home_DBX->private_tag);
    DBX_flash_tag = (struct st_DBX_flash_tag*)DBX_device_tag->DBX_medium_tag;
    chip = DBX_flash_tag->chip;
    __DFFSD_read_FDT_item(DBX_flash_tag,
                          (uint32_t)fp->file_medium_tag,&FDT_item);
    if((FDT_item.mattr & cn_FS_ATTR_READ_ONLY)
                || (FDT_item.mattr & cn_FS_ATTR_DIRECTORY))
        return 0;       //ֻ���ļ���Ŀ¼����ִ�����ó��ȵĲ���
    //��������if����ȷ��ԭ�ļ�ռ�õĿ��������ļ���������Ŀ���
    if(fp->file_size == 0)
        origin_blocks = 1;
    else
        origin_blocks = (u32)((fp->file_size + chip->block_size -1)/chip->block_size);
    if(new_size < 0)
        new_size = 0;
    if(new_size == 0)
        new_blocks = 1;
    else
        new_blocks = (u32)((new_size + chip->block_size -1)/chip->block_size);
    last_block_no = __DFFSD_last_block(DBX_flash_tag,fp);
    if(origin_blocks < new_blocks)     //�ļ�ռ�ÿ���������
    {
        for(loop = origin_blocks; loop < new_blocks; loop++)
        {
            next_block_no = __DFFSD_allocate_block(DBX_flash_tag);
            if(next_block_no != cn_limit_uint32)
            {
                __DFFSD_add_MAT_item(DBX_flash_tag,last_block_no,next_block_no);
                last_block_no = next_block_no;
            }else
                break;
        }
        if(loop == new_blocks)
            result = new_size;
        else
            result = (sint64_t)loop * chip->block_size;
    }else if(origin_blocks > new_blocks)     //�ļ�ռ�ÿ��������
    {
        result = new_size;
        for(loop = origin_blocks; loop > new_blocks; loop--)
        {
            next_block_no = last_block_no;
            last_block_no = DBX_flash_tag->DDR_MAT[next_block_no].previous;
            __DFFSD_free_block(DBX_flash_tag,next_block_no);
        }
        //���һ������ָ��ָ���Լ�
        DBX_flash_tag->DDR_MAT[last_block_no].next = last_block_no;
    }else           //ռ�ÿ�������
        result = new_size;
    fp->file_size = result;
    //���´����д�������������������дָ�룬���ѷǷ�ָ��(���ļ����̶������ļ�
    //���ȵ�ָ��λ��)�Ƶ��Ϸ�λ�á�
    if(fp->p_read_buf != NULL)      //��������ָ��ǿգ�˵���ж�������
    {
        if(fp->read_ptr > result)   //��ָ�����ļ��ߴ����
        {
            ring_flush(fp->p_read_buf); //��ն�������
            fp->read_ptr = result;      //��ָ��ص��ļ�ĩ
        }else
        {
            temp = fp->read_ptr + ring_check(fp->p_read_buf);
            //��ָ��δ�����ļ����ȵ��������������ݳ����ļ����ȣ����������ֿ���
            if(temp > result)
            {
                ring_skip_tail(fp->p_read_buf,(u32)(temp-result));
            }
        }
    }
    if(fp->p_write_buf != NULL)     //д������ָ��ǿգ�˵����д������
    {
        if(fp->write_ptr > result)  //дָ�볬���ļ�����
        {
            temp = result - fp->write_ptr;  //���㳬������
            ring_skip_tail(fp->p_write_buf,(u32)temp);   //���������ļ����ȵĲ��ҿ���
                                                    //���ڻ������е����ݡ�
            fp->write_ptr = result; //дָ��ص��ļ�ĩ
        }else
        {
            //дָ��û�г����ļ����ȣ����账��
        }
    }
   __DFFSD_update_FDT_file_size(DBX_flash_tag,fp,result);
   __DFFSD_write_DDR(DBX_flash_tag);   //�����޸�DDR,д��flash
    return result;
}

//----�����ļ�ָ��-------------------------------------------------------------
//���ܣ����ļ�ָ�����õ�ָ����λ�ã�����Ӧ��ͬ����д��������
//������fp�����������ļ�ָ��
//      offset���ƶ���λ��
//      whence���Ӻδ���ʼ�����ƶ����ȣ��μ�SEEK_CUR�ȵĶ���
//���أ�0=�ɹ���-1=ʧ��
//-----------------------------------------------------------------------------
uint32_t DFFSD_seek_file(struct file_rsc *fp,struct seek_para *position)
{
    struct st_DBX_device_tag *DBX_device_tag;
    struct st_DBX_flash_tag *DBX_flash_tag;
    sint64_t new_position,temp;
    uint32_t buffed_size;
    uint8_t  whence;
    if((position == NULL) ||(fp == NULL))
        return -1;
    DBX_device_tag = (struct st_DBX_device_tag *)(fp->home_DBX->private_tag);
    whence = position->whence;
    DBX_flash_tag = (struct st_DBX_flash_tag*)DBX_device_tag->DBX_medium_tag;
    switch (fp->open_mode)
    {
        case enum_r_rb:           //ֻ���ļ������ƶ���ָ��Ͷ�������
        case enum_a_ab_plus:      //д׷�ӷ�ʽ��дָ�벻�ܱ䣬��ָ��ķ�ʽ��
                                //ֻ���ļ�һ��
        {
            if(whence == SEEK_SET)
                new_position = position->offset;
            else if(whence == SEEK_CUR)
                new_position = position->offset + fp->read_ptr;
            else if(whence == SEEK_END)
                new_position = fp->file_size + position->offset;
            else
                return -1;
            temp = new_position - fp->read_ptr;
            buffed_size = ring_check(fp->p_read_buf);
            if((temp > 0) && (temp < buffed_size))
                //���������ƶ����Ȼ������е�������
                ring_dumb_read(fp->p_read_buf,(ptu32_t)temp);
            else
                ring_flush(fp->p_read_buf);//��ǰ�ƻ����ƶ������ڻ�������������
            if(new_position > fp->file_size)
                fp->read_ptr = fp->file_size;
            else if(new_position < 0)
                fp->read_ptr = 0;
            else
                fp->read_ptr = new_position;
        }break;
        case enum_w_wb:   //ֻд�ļ������ƶ�дָ��
        {
            __DFFSD_write_buf_to_flash(DBX_flash_tag,fp);
            if(whence == SEEK_SET)
                new_position = position->offset;
            else if(whence == SEEK_CUR)
                new_position = position->offset + fp->write_ptr;
            else if(whence == SEEK_END)
                new_position = fp->file_size - position->offset;
            else
                return -1;
            if(new_position > fp->file_size)
            {
                //�ӳ��ļ����������洢����������������ӵĴ洢��
                if(__DFFSD_set_file_size(fp,new_position) != new_position)
                    return -1;
                else
                {
                    fp->write_ptr = new_position;   //����дָ��
                }
            }else if(new_position < 0)
                fp->write_ptr = 0;
            else
                fp->write_ptr = new_position;
        }break;
        case enum_a_ab:   //׷��д��ʽ��seek������Ч
        {
        }break;
        case enum_r_rb_plus:  //�����߶��ǿɶ�д��ʽ����дָ���غϣ�����ʽ��ͬ
        case enum_w_wb_plus:
        {
            if(whence == SEEK_SET)
                new_position = position->offset;
            else if(whence == SEEK_CUR)
                new_position = position->offset + fp->read_ptr;
            else if(whence == SEEK_END)
                new_position = fp->file_size + position->offset;
            else
                return -1;
            __DFFSD_write_buf_to_flash(DBX_flash_tag,fp);//д���������ݱ���д��

            if(new_position > fp->file_size)    //��λ�ó����ļ�����
            {
                //�ӳ��ļ����������洢����������ʼ�������ӵĴ洢��
                if(__DFFSD_set_file_size(fp,new_position) != new_position)
                    return -1;
                else
                {
                    fp->write_ptr = new_position;   //����дָ��
                    fp->read_ptr = new_position;    //���ö�ָ��
                }
            }else if(new_position < 0)  //��λ��С��0����Ϊ0
            {
                fp->write_ptr = 0;      //д�������Ѿ�д�룬����дָ�뼴��
                fp->read_ptr = 0;    //���ö�ָ�룬��ָ��Ͷ����������Զ�������
                ring_flush(fp->p_read_buf); //��ն�������
            }
            else
            {
                fp->write_ptr = new_position;//д�������Ѿ�д�룬����дָ�뼴��
                fp->read_ptr = new_position;    //���ö�ָ��
                if(new_position < fp->read_ptr) //��λ��ʹ��ָ�����(���ļ���)
                {
                    ring_flush(fp->p_read_buf); //������������ȫ������
                }else
                {
                    //���㻺���������������ļ���ʲôλ��
                    temp = fp->read_ptr + ring_check(fp->p_read_buf);
                    if(new_position < temp)
                    {//��ָ��ǰ�ƣ���δ���������������ǵķ�Χ��
                        //�����������ݲ�������
                        ring_dumb_read(fp->p_read_buf,(u32)(temp-new_position));
                    }else
                    {//��ָ��ǰ�ƣ������������������ǵķ�Χ��
                        ring_flush(fp->p_read_buf);     //������������ȫ������
                    }
                }
            }
        }break;
        default: return -1;
    }
    return 0;
}

//----������Ŀ���ļ�/Ŀ¼��----------------------------------------------------
//���ܣ������ļ�(Ŀ¼)��attr��������������Ŀ¼�����ļ�����������ļ�����ͬʱ����
//      1��洢����ɾ���ļ�����ʹ�ļ�����Ϊ0ʱ��Ҳ��������һ���ͷš���֮���κ�
//      ����£��ļ�����ռ��1��洢��
//������name��Ŀ¼���ļ�����
//      parent����Ŀ¼ָ�롣
//      attr�����ļ���Ŀ¼��������
//���أ�true=�ɹ���false=ʧ�ܣ�һ������Ϊ�ļ���û���㹻����������
//��ע��������������������ɵ����߱�֤����Ϊ�洢���ʣ�ר�ش洢���ݵ�ְ���Ƿ�
//      ������������һ������Ρ�
//-----------------------------------------------------------------------------
bool_t DFFSD_create_file(char *name,struct file_rsc *parent,
                         union file_attrs attr)
{
    struct st_DBX_device_tag *DBX_device_tag;
    struct flash_chip *chip;
    uint32_t FDT_item_no_parent,FDT_item_no_eldest,FDT_item_no_least;
    uint32_t FDT_item_no_me,block_me,temp;
    struct fdt_info FDT_item_me,FDT_item_parent,FDT_item_eldest,FDT_item_least;
    struct st_DBX_flash_tag *DBX_flash_tag;

    if(parent == NULL)
        return false;
    DBX_device_tag =(struct st_DBX_device_tag *)(parent->home_DBX->private_tag);
    DBX_flash_tag = (struct st_DBX_flash_tag*)DBX_device_tag->DBX_medium_tag;
    chip = DBX_flash_tag->chip;
    FDT_item_no_parent = (uint32_t)parent->file_medium_tag;
    //����Ŀ¼��FDT��Ŀ
    __DFFSD_read_FDT_item(DBX_flash_tag,FDT_item_no_parent,&FDT_item_parent);
    if(!(FDT_item_parent.mattr & cn_FS_ATTR_DIRECTORY))
        return false;       //parent����һ��Ŀ¼�������ļ�
    FDT_item_no_me = __DFFSD_allocate_FDT_item(DBX_flash_tag);//����һ��FDT��Ŀ
    //debug Ҫ��Ҫ�Է����FDT���м�⣬�п����Ѿ���ʹ���ˡ������ʹ���ˣ�˵��
    //FDT�����ˣ���������ˡ����Բ����÷���ĳ������⡣��ͱ����ڴ�����ʱ��С��
    //��С�ģ�ǧ���ܽ����ɹ��ˣ���û�дӿ�������Ū�á�
    if(FDT_item_no_me == cn_limit_uint32)   //���䲻�ɹ�
        return false;
    if(FDT_item_no_parent == 0)
    {
        //��Ŀ¼�Ǹ�Ŀ¼������ʱFDT��Ŀʱ���޸ĸ�Ŀ¼��Ŀ�������ض�
        __DFFSD_read_FDT_item(DBX_flash_tag,0,&FDT_item_parent);
    }
    if( ! attr.bits.folder)
    {
        block_me = __DFFSD_allocate_block(DBX_flash_tag);
        if(block_me == cn_limit_uint32)
        {
            __DFFSD_free_FDT_item(DBX_flash_tag,FDT_item_no_me);
            return false;
        }else
        {
            __fill_little_32bit(FDT_item_me.fstart_dson,0,block_me);
            DBX_flash_tag->DDR_MAT[block_me].attr = cn_file_block_start;
            DBX_flash_tag->DDR_MAT[block_me].previous = FDT_item_no_me;
            DBX_flash_tag->DDR_MAT[block_me].next = block_me;
            //����last_block_no��MAT����λ�ô���DDR�����ǵڼ���
            temp = __DFFSD_MAT_start(DBX_flash_tag);
            temp=(temp + block_me*4*2) / chip->block_size;
            //DDR_bak�б�Ǹÿ�Ϊδд��
            DBX_flash_tag->writed_DDR_bak[temp] = false;
            //DDR_main�б�Ǹÿ�Ϊδд��
            DBX_flash_tag->writed_DDR_main[temp] = false;
        }
    }else
    {
        block_me = cn_limit_uint32;
        __fill_little_32bit(FDT_item_me.fstart_dson,0,cn_limit_uint32);
    }
    __DFFSD_asm_FDT_item(&FDT_item_me,attr,name);
    __fill_little_32bit(FDT_item_me.parent,0,FDT_item_no_parent);
    FDT_item_no_eldest = __pick_little_32bit(FDT_item_parent.fstart_dson,0);
    if(FDT_item_no_eldest == cn_limit_uint32)   //��Ŀ¼�ǿ�Ŀ¼
    {
        //�����½�Ŀ¼��
        __fill_little_32bit(FDT_item_me.previous,0,FDT_item_no_me);
        __fill_little_32bit(FDT_item_me.next,0,FDT_item_no_me);
        //�½�Ŀ¼��д��flash
        __DFFSD_write_FDT_item(DBX_flash_tag,FDT_item_no_me,&FDT_item_me);
        //��Ŀ¼�������ָ���½�Ŀ¼��
        __fill_little_32bit(FDT_item_parent.fstart_dson,0,FDT_item_no_me);
        __DFFSD_write_FDT_item(DBX_flash_tag,FDT_item_no_parent,
                               &FDT_item_parent);   //��Ŀ¼�޸ĺ�д��flash
    }else       //��Ŀ¼��������(����Ŀ¼���ļ�)
    {
        __DFFSD_read_FDT_item(DBX_flash_tag,FDT_item_no_eldest,&FDT_item_eldest);
        FDT_item_no_least = __pick_little_32bit(FDT_item_eldest.previous,0);
        //�����½�Ŀ¼��
        __fill_little_32bit(FDT_item_me.previous,0,FDT_item_no_least);
        __fill_little_32bit(FDT_item_me.next,0,FDT_item_no_eldest);
        //�½�Ŀ¼��д��flash
        __DFFSD_write_FDT_item(DBX_flash_tag,FDT_item_no_me,&FDT_item_me);
        if(FDT_item_no_least == FDT_item_no_eldest) //��Ŀ¼��ֻ��һ������
        {
            //�������ǰ��ָ���ָ���½�Ŀ¼��
            __fill_little_32bit(FDT_item_eldest.previous,0,FDT_item_no_me);
            __fill_little_32bit(FDT_item_eldest.next,0,FDT_item_no_me);
            //������д��flash
            __DFFSD_write_FDT_item(DBX_flash_tag,
                                   FDT_item_no_eldest,&FDT_item_eldest);
        }else       //��Ŀ¼���ж������
        {
            //��һ�������ǰָ��ָ���½�Ŀ¼��
            __fill_little_32bit(FDT_item_eldest.previous,0,FDT_item_no_me);
            //��һ������д��flash
            __DFFSD_write_FDT_item(DBX_flash_tag,
                                   FDT_item_no_eldest,&FDT_item_eldest);
            //�������һ������
            __DFFSD_read_FDT_item(DBX_flash_tag,
                                  FDT_item_no_least,&FDT_item_least);
            //�½�����ĺ�ָ��ָ���½�Ŀ¼��
            __fill_little_32bit(FDT_item_least.next,0,FDT_item_no_me);
            //���һ������д��flash
            __DFFSD_write_FDT_item(DBX_flash_tag,
                                   FDT_item_no_least,&FDT_item_least);
        }
    }
    __DFFSD_write_DDR(DBX_flash_tag);
    return true;
}

//----������Ŀ���ļ�/Ŀ¼��----------------------------------------------------
//���ܣ������ļ�(Ŀ¼)��attr��������������Ŀ¼�����ļ�����������ļ�����ͬʱ����
//      1��洢����ɾ���ļ�����ʹ�ļ�����Ϊ0ʱ��Ҳ��������һ���ͷš���֮���κ�
//      ����£��ļ�����ռ��1��洢��
//������name��Ŀ¼���ļ�����
//      parent����Ŀ¼ָ�롣
//      attr�����ļ���Ŀ¼��������
//���أ�true=�ɹ���false=ʧ�ܣ�һ������Ϊ�ļ���û���㹻����������
//��ע��������������������ɵ����߱�֤����Ϊ�洢���ʣ�ר�ش洢���ݵ�ְ���Ƿ�
//      ������������һ������Ρ�
//-----------------------------------------------------------------------------
bool_t DFFSD_move_file(struct file_rsc *src_fp,	struct file_rsc *dest_fp)
{
    struct st_DBX_device_tag *DBX_device_tag;
    uint32_t src_FDT_item_no,dest_FDT_item_no,dest_FDT_item_no_parent;
    uint32_t FDT_item_no_previous,FDT_item_no_next;
    struct fdt_info src_FDT_item,dest_FDT_item;
    struct fdt_info FDT_item_previous,FDT_item_next;
    struct st_DBX_flash_tag *DBX_flash_tag;

    if(dest_fp == NULL || src_fp == NULL)
        return false;    
    DBX_device_tag =(struct st_DBX_device_tag *)(src_fp->home_DBX->private_tag);
    DBX_flash_tag = (struct st_DBX_flash_tag*)DBX_device_tag->DBX_medium_tag;    
    
    src_FDT_item_no = (uint32_t)src_fp->file_medium_tag;
    dest_FDT_item_no = (uint32_t)dest_fp->file_medium_tag;
    //����Ŀ¼��FDT��Ŀ
    __DFFSD_read_FDT_item(DBX_flash_tag,src_FDT_item_no,&src_FDT_item);
    __DFFSD_read_FDT_item(DBX_flash_tag,dest_FDT_item_no,&dest_FDT_item);
    if((src_FDT_item.mattr & cn_FS_ATTR_DIRECTORY)||
                                (dest_FDT_item.mattr & cn_FS_ATTR_DIRECTORY))
        return false;       //��Ŀ¼

    dest_FDT_item_no_parent = __pick_little_32bit(dest_FDT_item.parent,0); 
    __fill_little_32bit(src_FDT_item.parent,0,dest_FDT_item_no_parent);
	__DFFSD_write_FDT_item(DBX_flash_tag,src_FDT_item_no,&src_FDT_item);
    
    

	FDT_item_no_previous = __pick_little_32bit(dest_FDT_item.previous,0);
 	FDT_item_no_next = __pick_little_32bit(dest_FDT_item.next,0);
    //���ƶ���ֻ��һ��
	if((FDT_item_no_previous == src_FDT_item_no)&&(FDT_item_no_next == src_FDT_item_no))
    {
        __DFFSD_free_FDT_item(DBX_flash_tag,dest_FDT_item_no);
                //�����½�Ŀ¼��
        __fill_little_32bit(src_FDT_item.previous,0,src_FDT_item_no);
        __fill_little_32bit(src_FDT_item.next,0,src_FDT_item_no);
        //�½�Ŀ¼��д��flash
        __DFFSD_write_FDT_item(DBX_flash_tag,src_FDT_item_no,&src_FDT_item); 
        //ֻ��һ�ûʲô�ô���	
    }else 
    {    
     	if((FDT_item_no_previous != src_FDT_item_no)&&(FDT_item_no_previous==FDT_item_no_next))  
        {//���ƶ��ģ���һ���ֵ�Ŀ¼���ļ���
            //������һ���ǰָ��ͺ�ָ�룬��ָ���Լ���FDT_item_no_previous��FDT_item_no_next
            //��ͬһ�����һ��
         	__DFFSD_read_FDT_item(DBX_flash_tag,
                                  FDT_item_no_previous,&FDT_item_previous);
            __fill_little_32bit(FDT_item_previous.previous,0,FDT_item_no_previous);
            __fill_little_32bit(FDT_item_previous.next,0,FDT_item_no_previous);
           __DFFSD_write_FDT_item(DBX_flash_tag,FDT_item_no_previous,&FDT_item_previous);
        }
    	else
        {
        	__DFFSD_read_FDT_item(DBX_flash_tag,
                                  FDT_item_no_previous,&FDT_item_previous);
        	__DFFSD_read_FDT_item(DBX_flash_tag,
                                  FDT_item_no_next,&FDT_item_next);
            //���ƶ����ǰ��Ŀ�ĺ�ָ�룬ָ���ƶ���ĺ���Ŀ
        	__fill_little_32bit(FDT_item_previous.next,0,FDT_item_no_next);
            //���ƶ���ĺ���Ŀ��ǰָ�룬ָ���ƶ����ǰ��Ŀ
            __fill_little_32bit(FDT_item_next.previous,0,FDT_item_no_previous);
        	__DFFSD_write_FDT_item(DBX_flash_tag,FDT_item_no_previous,&FDT_item_previous);
        	__DFFSD_write_FDT_item(DBX_flash_tag,FDT_item_no_next,&FDT_item_next);
        }
    }

     
	FDT_item_no_previous = __pick_little_32bit(src_FDT_item.previous,0);
 	FDT_item_no_next = __pick_little_32bit(src_FDT_item.next,0);
    //���ƶ���ֻ��һ��
	if((FDT_item_no_previous == src_FDT_item_no)&&(FDT_item_no_next == src_FDT_item_no))
    {
        //ֻ��һ�ûʲô�ô���	
    }else 
    {    
     	if((FDT_item_no_previous != src_FDT_item_no)&&(FDT_item_no_previous==FDT_item_no_next))  
        {//���ƶ��ģ���һ���ֵ�Ŀ¼���ļ���
            //������һ���ǰָ��ͺ�ָ�룬��ָ���Լ���FDT_item_no_previous��FDT_item_no_next
            //��ͬһ�����һ��
         	__DFFSD_read_FDT_item(DBX_flash_tag,
                                  FDT_item_no_previous,&FDT_item_previous);
            __fill_little_32bit(FDT_item_previous.previous,0,FDT_item_no_previous);
            __fill_little_32bit(FDT_item_previous.next,0,FDT_item_no_previous);
           __DFFSD_write_FDT_item(DBX_flash_tag,FDT_item_no_previous,&FDT_item_previous);
        }
    	else
        {
        	__DFFSD_read_FDT_item(DBX_flash_tag,
                                  FDT_item_no_previous,&FDT_item_previous);
        	__DFFSD_read_FDT_item(DBX_flash_tag,
                                  FDT_item_no_next,&FDT_item_next);
            //���ƶ����ǰ��Ŀ�ĺ�ָ�룬ָ���ƶ���ĺ���Ŀ
        	__fill_little_32bit(FDT_item_previous.next,0,FDT_item_no_next);
            //���ƶ���ĺ���Ŀ��ǰָ�룬ָ���ƶ����ǰ��Ŀ
            __fill_little_32bit(FDT_item_next.previous,0,FDT_item_no_previous);
        	__DFFSD_write_FDT_item(DBX_flash_tag,FDT_item_no_previous,&FDT_item_previous);
        	__DFFSD_write_FDT_item(DBX_flash_tag,FDT_item_no_next,&FDT_item_next);
        }
    }

    __DFFSD_write_DDR(DBX_flash_tag);//ddrҲ��ı䣬���޸ı䣬�������д
    return true;
}

//----����ļ��е����ļ���Ŀ¼����---------------------------------------------
//���ܣ�����ļ��е����ļ���Ŀ¼��������������Ŀ¼������Ŀ
//������DBX_device_tag�����������ļ���ָ�룬ͨ�ýṹ����flashר�á�
//      fp��Ŀ���ļ��е��ļ�ָ��
//���أ����ļ���Ŀ¼����
//-----------------------------------------------------------------------------
uint32_t DFFSD_check_folder(struct file_rsc *parent)
{
    struct st_DBX_device_tag *DBX_device_tag;
    struct fdt_info FDT_item;
    struct st_DBX_flash_tag *DBX_flash_tag;
    uint32_t FDT_item_no,FDT_item_no_next;
    uint32_t result;
    if(parent == NULL)
        return 0;
    if( ! parent->attr.bits.folder)      //�����ļ�������Ŀ¼
        return 0;
    result = 0;
    DBX_device_tag = (struct st_DBX_device_tag *)(parent->home_DBX->private_tag);
    DBX_flash_tag = (struct st_DBX_flash_tag *)DBX_device_tag->DBX_medium_tag;
    FDT_item_no = (uint32_t)parent->file_medium_tag;
    __DFFSD_read_FDT_item(DBX_flash_tag,FDT_item_no,&FDT_item);
    //��һ������Ŀ��FDT��Ŀ��
    FDT_item_no = __pick_little_32bit(FDT_item.fstart_dson,0);
    if(FDT_item_no == cn_limit_uint32)
        return 0;
    FDT_item_no_next = FDT_item_no;
    do
    {
        result++;
        __DFFSD_read_FDT_item(DBX_flash_tag,FDT_item_no_next,&FDT_item);
        FDT_item_no_next = __pick_little_32bit(FDT_item.next,0);
    }while(FDT_item_no != FDT_item_no_next);
    return result;
}

//----ɾ����Ŀ���ļ�/Ŀ¼��---------------------------------------------------
//���ܣ�ɾ��һ���ļ�(Ŀ¼)��ֻ��ɾ����Ŀ¼���Ѿ��رյ��ļ���
//������fp����ɾ����Ŀ¼���ļ���ָ��
//���أ�true=�ɹ���false=ʧ��
//-----------------------------------------------------------------------------
bool_t DFFSD_remove_file(struct file_rsc *fp)
{
    struct fdt_info FDT_item;
    struct st_DBX_device_tag *DBX_device_tag;
    struct st_DBX_flash_tag *DBX_flash_tag;
    struct flash_chip *chip;
    uint32_t FDT_item_no,loop,block_no,block_no_next,blocks;
    if(fp == NULL)
        return false;
    if(( ! fp->attr.bits.folder) && (fp->open_counter != 0))
        return false;   //fp��һ���Ѿ��򿪵��ļ�
    if(fp->attr.bits.folder)
    {
        if(DFFSD_check_folder(fp) != 0)
            return false;   //��һ���ǿ�Ŀ¼
    }
    DBX_device_tag = (struct st_DBX_device_tag *)(fp->home_DBX->private_tag);
    DBX_flash_tag = (struct st_DBX_flash_tag *)DBX_device_tag->DBX_medium_tag;
    chip = DBX_flash_tag->chip;
    FDT_item_no = (uint32_t)fp->file_medium_tag;
    if( ! fp->attr.bits.folder) //�Ǹ��ļ�����Ҫ�ͷ��ļ�ռ�õĴ洢��
    {
        if(fp->file_size == 0)  //0�����ļ�Ҳռ��1��
            blocks = 1;
        else
            blocks = (u32)((fp->file_size + (s64)chip->block_size -1) / chip->block_size);
        __DFFSD_read_FDT_item(DBX_flash_tag,FDT_item_no,&FDT_item);//ȡĿ¼��
        block_no = __pick_little_32bit(FDT_item.fstart_dson,0);//ȡ�ļ��׿���
        for(loop = 0; loop < blocks; loop++)
        {
            //������һ����
            block_no_next = DBX_flash_tag->DDR_MAT[block_no].next;
            __DFFSD_free_block(DBX_flash_tag,block_no); //�ͷ�һ��
            block_no = block_no_next;
        }
    }
    __DFFSD_free_FDT_item(DBX_flash_tag,FDT_item_no); //�ͷ�FDT��
    
    __DFFSD_write_DDR(DBX_flash_tag); 
    return true;
}

//----����һ��Ŀ¼������-------------------------------------------------------
//����: ��current_file��ʼ,��ȡ��parent����һ���ļ���ָ��,ֱ��parent
//      �������������.
//����: parent,��Ҫ��������֦�����Ƚ��
//      current_file,��ǰ����λ��,�����ʾ��һ�β���
//����: ������������ָ��(�������ļ���Ŀ¼)
//��ע: ���������������Ϊwindows�� FindFirstFile��������������ϱ�����
//      ��Ŀ¼�µ��ļ�
//      ��һ�α���ʱ(��current==NULL)Ϊ��־��ϵͳ��Ϊstruct file_rsc�ṹ�����ڴ棬
//      ���һ�Σ����ͷ��ڴ档����û���ȷ�ص���DFFSD_item_traversal_son������
//      ����Ŀ¼���ڴ������ȫ����������Ϊstruct file_rsc�ṹ������ڴ潫��
//      Ҫ�û��ֶ��ͷ�
//---------------------------------------------------------------------
struct file_rsc * DFFSD_item_traversal_son(struct file_rsc *parent,
                                        	struct file_rsc *current)
{
	uint32_t FDT_item_no,first_FDT_item_no;
	struct fdt_info FDT_item;
	struct st_DBX_device_tag *DBX_device_tag;
	struct st_DBX_flash_tag *DBX_flash_tag;

    if(parent == NULL)
        return NULL;
    if(!parent->attr.bits.folder)       //��Ŀ¼�Ǹ��ļ���
        return NULL;
    if(parent->file_medium_tag == cn_limit_uint32)
        return NULL;
    
	DBX_device_tag =(struct st_DBX_device_tag *)(parent->home_DBX->private_tag);
	DBX_flash_tag = (struct st_DBX_flash_tag*)DBX_device_tag->DBX_medium_tag;
   	__DFFSD_read_FDT_item(DBX_flash_tag,parent->file_medium_tag,&FDT_item);
	first_FDT_item_no = __pick_little_32bit(FDT_item.fstart_dson,0);
    if(first_FDT_item_no == cn_limit_uint32)    //��Ŀ¼�Ǹ���Ŀ¼
        return NULL;

    if(current == NULL)    //���curent_file�ǿյģ����ص�һ������
    {
        current = m_malloc(sizeof(struct file_rsc),cn_timeout_forever);
        if(current == NULL)
            return NULL;
    	__DFFSD_read_FDT_item(DBX_flash_tag,first_FDT_item_no,&FDT_item);
    	__DFFSD_uasm_FDT_item(DBX_flash_tag,current,&FDT_item);
        current->home_DBX = parent->home_DBX;
    	current->file_medium_tag = (ptu32_t)first_FDT_item_no;
    }
    else if(current->file_medium_tag != cn_limit_uint32)
    {
        __DFFSD_read_FDT_item(DBX_flash_tag,current->file_medium_tag,&FDT_item); 
        //parent��cn_limit_uint32,˵��current_file��Ӧ���ļ��Ѿ���ɾ��
        if(__pick_little_32bit(FDT_item.parent,0) == cn_limit_uint32)
        {
            //��ǰ�ļ���ɾ����ȡ��һ������
            __DFFSD_read_FDT_item(DBX_flash_tag,first_FDT_item_no,&FDT_item);
            __DFFSD_uasm_FDT_item(DBX_flash_tag,current,&FDT_item);
            current->home_DBX = parent->home_DBX;
            current->file_medium_tag = (ptu32_t)first_FDT_item_no;
        }
        else
        {
          	FDT_item_no = __pick_little_32bit(FDT_item.next,0);
            if(FDT_item_no == first_FDT_item_no)    //current_file�Ѿ������һ��
            {
                m_free(current);
                return NULL;
            }
        	__DFFSD_read_FDT_item(DBX_flash_tag,FDT_item_no,&FDT_item);
            __DFFSD_uasm_FDT_item(DBX_flash_tag,current,&FDT_item);
            current->home_DBX = parent->home_DBX;
            current->file_medium_tag = (ptu32_t)FDT_item_no;
        }
    }
    else
    {
        return NULL;    //��ǰλ�÷Ƿ�
    }
    return current;
}


//----�Ƚ�����-----------------------------------------------------------------
//����: �Ƚ������ļ�(Ŀ¼)���ַ����Ƿ���ȣ����ļ�ϵͳ֧��255�ַ�����flash
//      driverֻ֧��cn_file_name_len���ַ�����˵�fs_name�ĳ��ȳ���
//      cn_file_name_lenʱ����β�Ƚϡ�����β�󳤶��Բ���ȣ�ֱ�ӷ���false������
//      ����ȣ������ַ��Ƚϣ�ȫ�ȷ���true�����򷵻�false��
//����: fs_name�����ļ�ϵͳ�ṩ���ļ���ָ��
//      FDT_name��FDT���ж�ȡ���ļ���ָ��
//����: true = ��ȣ�false=�����
//----------------------------------------------------------------------------
bool_t __DFFSD_cmp_file_name(char *fs_name,char *FDT_name)
{
    uint32_t fs_len,FDT_len;
    //fs_name���Ѿ������ַ������ȺϷ��Լ���ָ��
    fs_len = strlen(fs_name);
    //FDT_name���Ѿ������ַ������ȺϷ��Լ���ָ��
    FDT_len = strlen(FDT_name);
    if(fs_len > cn_flash_file_name_limit)
        fs_len = cn_flash_file_name_limit;
    if(fs_len != FDT_len)
        return false;
    fs_len = fs_len > FDT_len? FDT_len:fs_len;
    for(FDT_len = 0; FDT_len < fs_len; FDT_len++)
        if(fs_name[FDT_len] != FDT_name[FDT_len])
            return false;
    return true;
}

//----�����ļ�������-----------------------------------------------------------
//����: �����ļ��Ĵ�ģʽ��Ϊ�ļ����仺������
//����: DBX_flash_tag����������flash�ļ���Ĵ洢ý���ǩ
//      fp�����ļ�ϵͳ�ṩ���ļ���ָ��
//      mode���ļ�����ģʽ
//����: true = ��ȣ�false=�����
//----------------------------------------------------------------------------
bool_t __DFFSD_allocate_file_buf(struct st_DBX_flash_tag *DBX_flash_tag,
                              struct file_rsc *fp,
                              enum file_open_mode mode)
{
    struct flash_chip *chip;
    uint32_t read_buf_len;
    uint32_t write_buf_len;
    uint8_t *buf;
    uint8_t *buf1;
    chip = DBX_flash_tag->chip;
    read_buf_len = chip->DBX_read_buf_size;
    write_buf_len = chip->DBX_write_buf_size;
    if(fp->attr.bits.folder)     //FDT��Ŀ��һ��Ŀ¼
    {
        ring_init(&fp->read_rw_buf,NULL,0);     //Ŀ¼�Ķ���������Ϊ��
        ring_init(&fp->write_buf,NULL,0);       //Ŀ¼��д��������Ϊ��
        fp->p_read_buf = NULL;
        fp->p_write_buf = NULL;
        fp->read_ptr = 0;
        fp->write_ptr = 0;
        fp->file_size = 0;
    }else       //��һ���ļ�����Ҫ����mode�����д������
    {
        switch(mode)
        {
            case enum_r_rb:
            {
                buf =(uint8_t*)m_malloc(read_buf_len,0);//��ģʽֻ�ж�������
                if(buf == NULL)
                    return false;           //����������ʧ�ܣ����ش���
                ring_init(&fp->read_rw_buf,buf,read_buf_len);   //��ʼ����������
                ring_init(&fp->write_buf,NULL,0);           //��ʼ��д������Ϊ��
                fp->p_read_buf = &fp->read_rw_buf;  //��������ָ�븳ֵ
                fp->p_write_buf = NULL;             //д������ָ���ÿ�
                fp->read_ptr = 0;                   //��λ����0
                fp->write_ptr = 0;                  //дλ����0
            }break;
            case enum_w_wb:
            {
                buf =(uint8_t*)m_malloc(write_buf_len,0);//��ģʽֻ��д������
                if(buf == NULL)
                    return false;           //����������ʧ�ܣ����ش���
                ring_init(&fp->read_rw_buf,NULL,0);         //��ʼ����������Ϊ��
                ring_init(&fp->write_buf,buf,write_buf_len);//��ʼ��д������
                fp->p_read_buf = NULL;              //��������ָ���ÿ�
                fp->p_write_buf = &fp->write_buf;   //д������ָ�븳ֵ
                fp->read_ptr = 0;                   //��λ����0
                fp->write_ptr = 0;                  //дλ����0
                __DFFSD_set_file_size(fp,0);//��ģʽ��Ҫ���ļ����
            }break;
            case enum_a_ab:
            {
                buf =(uint8_t*)m_malloc(write_buf_len,0);//��ģʽֻ��д������
                if(buf == NULL)
                    return false;           //����������ʧ�ܣ����ش���
                ring_init(&fp->read_rw_buf,NULL,0);         //��ʼ����������Ϊ��
                ring_init(&fp->write_buf,buf,write_buf_len);//��ʼ��д������
                fp->p_read_buf = NULL;              //��������ָ���ÿ�
                fp->p_write_buf = &fp->write_buf;   //д������ָ�븳ֵ
                fp->read_ptr = 0;                   //��λ����0
                fp->write_ptr = fp->file_size;      //дλ��ָ���ļ�β
            }break;
            case enum_r_rb_plus:
            {
                buf = (uint8_t*)m_malloc(read_buf_len,0);      //�����������
                if(buf == NULL)
                    return false;           //����������ʧ�ܣ����ش���
                buf1 = (uint8_t*)m_malloc(write_buf_len,0);    //����д������
                if(buf1 == NULL)
                {

                    m_free(buf);
                return false;           //����������ʧ�ܣ����ش���
                }
                ring_init(&fp->read_rw_buf,buf,read_buf_len);   //��ʼ����������
                ring_init(&fp->write_buf,buf1,write_buf_len);   //��ʼ��д������
                fp->p_read_buf = &fp->read_rw_buf;      //���ö�������ָ��
                fp->p_write_buf = &fp->write_buf;       //����д������ָ��
                fp->read_ptr = 0;                       //��λ����0
                fp->write_ptr = 0;                      //дλ����0
            }break;
            case enum_w_wb_plus:
            {
                buf = (uint8_t*)m_malloc(read_buf_len,0);      //�����������
                if(buf == NULL)
                    return false;           //����������ʧ�ܣ����ش���
                buf1 = (uint8_t*)m_malloc(write_buf_len,0);    //����д������
                if(buf1 == NULL)
                {

                    m_free(buf);
                    return false;           //����������ʧ�ܣ����ش���
                }
                ring_init(&fp->read_rw_buf,buf,read_buf_len);   //��ʼ����������
                ring_init(&fp->write_buf,buf1,write_buf_len);   //��ʼ��д������
                fp->p_read_buf = &fp->read_rw_buf;      //���ö�������ָ��
                fp->p_write_buf = &fp->write_buf;       //����д������ָ��
                fp->read_ptr = 0;                       //��λ����0
                fp->write_ptr = 0;                      //дλ����0
                __DFFSD_set_file_size(fp,0);//��ģʽ��Ҫ���ļ����
            }break;
            case enum_a_ab_plus:
            {
                buf = (uint8_t*)m_malloc(read_buf_len,0);      //�����������
                if(buf == NULL)
                    return false;           //����������ʧ�ܣ����ش���
                buf1 = (uint8_t*)m_malloc(write_buf_len,0);    //����д������
                if(buf1 == NULL)
                {

                    m_free(buf);
                    return false;           //����������ʧ�ܣ����ش���
                }
                ring_init(&fp->read_rw_buf,buf,read_buf_len);   //��ʼ����������
                ring_init(&fp->write_buf,buf1,write_buf_len);   //��ʼ��д������
                fp->p_read_buf = &fp->read_rw_buf;      //���ö�������ָ��
                fp->p_write_buf = &fp->write_buf;       //����д������ָ��
                fp->read_ptr = 0;                       //��λ����0
                fp->write_ptr = fp->file_size;          //дλ��ָ���ļ�β
            }break;
            default:break;
        }
    }
    return true;
}

//----�򿪣��ļ�/Ŀ¼��--------------------------------------------------------
//���ܣ����ļ����в��Ҳ����ļ�(Ŀ¼)��������ļ�������ҪΪ�������д��������ֻ
//      �鸸Ŀ¼����������������
//������name���ļ���Ŀ¼����
//      parent���ļ�/Ŀ¼�ĸ�Ŀ¼��
//      result�������ҵ����ļ�����Ϣ
//      mode���ļ���Ŀ¼����ģʽ
//���أ�cn_fs_open_success,�ɹ����ļ�(Ŀ¼)
//      cn_fs_item_exist,�ļ�(Ŀ¼)���ڵ����ܴ�(һ����ģʽ������)
//      cn_fs_item_inexist,�ļ�(Ŀ¼)������
//      cn_limit_uint32����������
//----------------------------------------------------------------------------
uint32_t DFFSD_open_item(char *name,struct file_rsc *parent,
                       struct file_rsc *result,enum file_open_mode mode)
{
    uint32_t FDT_item_no,FDT_item_eldest;
    struct st_DBX_device_tag *DBX_device_tag;
    struct st_DBX_flash_tag *DBX_flash_tag;
    struct fdt_info FDT_item;
    bool_t found = false;

    if((parent == NULL) || (result == NULL))
        return cn_limit_uint32;
    DBX_device_tag = (struct st_DBX_device_tag *)(parent->home_DBX->private_tag);
    DBX_flash_tag = (struct st_DBX_flash_tag *)DBX_device_tag->DBX_medium_tag;

    FDT_item_no = (uint32_t)parent->file_medium_tag;
    //��ȡ��Ŀ¼��FDT����
    __DFFSD_read_FDT_item(DBX_flash_tag,FDT_item_no,&FDT_item);
    if(!(FDT_item.mattr & cn_FS_ATTR_DIRECTORY))
        return cn_limit_uint32;       //��Ŀ¼ʵ������һ���ļ�
    //��ȡ��Ŀ¼�ĵ�һ����Ŀ¼/�ļ���FDT�����
    FDT_item_eldest = __pick_little_32bit(FDT_item.fstart_dson,0);
    if(FDT_item_eldest == cn_limit_uint32)
        return cn_fs_item_inexist;  //parent��һ����Ŀ¼
    FDT_item_no = FDT_item_eldest;
    do  //ѭ����Ŀ¼��ֱ������
    {
        //��ȡ��FDT����
        __DFFSD_read_FDT_item(DBX_flash_tag,FDT_item_no,&FDT_item);
        FDT_item.name[cn_flash_file_name_limit] = '\0'; //�ַ������������ݴ���
        if(__DFFSD_cmp_file_name(name,FDT_item.name))
        {
            found = true;       //�ҵ�ƥ����ļ�(Ŀ¼)
            break;
        }else
        {
        	if(__pick_little_32bit(FDT_item.next,0) ==FDT_item_no)//������ѭ��
            	break;
            FDT_item_no = __pick_little_32bit(FDT_item.next,0);
            if(FDT_item_no == cn_limit_uint32)//��ֹ��ѭ��
                break;
        }
    }while(FDT_item_no != FDT_item_eldest);
    if(found)
    {
        result->file_medium_tag = (ptu32_t)FDT_item_no;
        result->file_semp = NULL;
        result->open_mode = mode;
        //��flash��FDT��Ŀ���ڴ澵��FDT_item����ȡ�ļ���Ϣ
        __DFFSD_uasm_FDT_item(DBX_flash_tag,result,&FDT_item);
        if(__DFFSD_allocate_file_buf(DBX_flash_tag,result,mode))//�����ļ�������
        {
            return cn_fs_open_success;
        }else
            return cn_fs_item_exist;
    }else
        return cn_fs_item_inexist;
}

//----���ң��ļ�/Ŀ¼��--------------------------------------------------------
//���ܣ����ļ����в��Ҳ����ļ�(Ŀ¼)��������ļ�������ҪΪ�������д��������
//������name���ļ���Ŀ¼����
//      parent���ļ�/Ŀ¼�ĸ�Ŀ¼��
//      result�������ҵ����ļ�����Ϣ
//���أ�true=�ļ�/Ŀ¼���ڣ�����result�з����ļ���Ϣ(�������ļ�������)��
//      false = �ļ�/Ŀ¼�����ڣ����޸�result��
//----------------------------------------------------------------------------
bool_t DFFSD_lookfor_item(char *name,struct file_rsc *parent,
                         struct file_rsc *result)
{
    uint32_t FDT_item_no,FDT_item_eldest;
    struct st_DBX_device_tag *DBX_device_tag;
    struct st_DBX_flash_tag *DBX_flash_tag;
    struct fdt_info FDT_item;
    bool_t found = false;
    if(parent == NULL)
        return false;
    if(result != NULL)
        rsc_clean_node(&result->file_node);
    DBX_device_tag = (struct st_DBX_device_tag *)(parent->home_DBX->private_tag);
    DBX_flash_tag = (struct st_DBX_flash_tag *)DBX_device_tag->DBX_medium_tag;
    FDT_item_no = (uint32_t)parent->file_medium_tag;
    //��ȡ��Ŀ¼��FDT����
    __DFFSD_read_FDT_item(DBX_flash_tag,FDT_item_no,&FDT_item);
    if(!(FDT_item.mattr & cn_FS_ATTR_DIRECTORY))
        return false;       //��Ŀ¼ʵ������һ���ļ�
    //��ȡ��Ŀ¼�ĵ�һ����Ŀ¼/�ļ���FDT�����
    FDT_item_eldest = __pick_little_32bit(FDT_item.fstart_dson,0);
    if(FDT_item_eldest == cn_limit_uint32)
        return false;  //parent��һ����Ŀ¼
    FDT_item_no = FDT_item_eldest;
    do  //ѭ����Ŀ¼��ֱ������
    {
        //��ȡ��FDT����
        __DFFSD_read_FDT_item(DBX_flash_tag,FDT_item_no,&FDT_item);
        FDT_item.name[cn_flash_file_name_limit] = '\0'; //�ַ������������ݴ���
        if(__DFFSD_cmp_file_name(name,FDT_item.name))
        {
            if(result != NULL)
            {
                result->file_medium_tag = (ptu32_t)FDT_item_no;
                result->file_semp = NULL;

            	result->home_DBX = parent->home_DBX;    
                //��flash��FDT��Ŀ���ڴ澵��FDT_item����ȡ�ļ���Ϣ
                __DFFSD_uasm_FDT_item(DBX_flash_tag,result,&FDT_item);
            }
            found = true;
            break;
        }else
        {
            FDT_item_no = __pick_little_32bit(FDT_item.next,0);
        }
    }while(FDT_item_no != FDT_item_eldest);
    return found;
}

//----�ر��ļ�(Ŀ¼)-----------------------------------------------------------
//����: �ر�һ���򿪵��ļ�(Ŀ¼)��������ļ������ͷŶ�д����������ʹ�ļ�����
//      opened_sum�����������Ŀ¼����ֻ��opened_sum������������ֻ�Ǵ���رչ���
//      ��洢������صĲ�����ϵͳ��Դ������file.cģ�鴦��
//������fp�����������ļ�ָ��
//���أ�true=�ɹ���false=ʧ��
//-----------------------------------------------------------------------------
bool_t DFFSD_close_item(struct file_rsc *fp)
{
    if(fp == NULL)
        return false;
    if(fp->attr.bits.folder)
    {
        //�Ǹ�Ŀ¼������ûʲô��Ҫ�����
    }else
    {
        if(ring_capacity(&fp->write_buf) != 0)    //�鿴�ļ�д�������Ƿ��
        {
            DFFSD_flush_file(fp);//д���������ݱ���д��
            m_free(ring_get_buf(&fp->write_buf)); //�ļ�д�������ǿգ��ͷ�֮
        }
        if(ring_capacity(&fp->read_rw_buf) != 0)     //�鿴�ļ����������Ƿ��
        {
            m_free(ring_get_buf(&fp->read_rw_buf));  //�ļ����������ǿգ��ͷ�֮
        }
    }
    return true;
}

//----�ļ���Ŀ¼������---------------------------------------------------------
//���ܣ��޸�һ���ļ���Ŀ¼�������֣������ֱ�����fp�С�fp�е����ֿ��Դﵽ255��
//      ������ֻ��ǰcn_flash_file_name_limit�ַ���Ч��
//������fp�����������ļ�ָ��
//���أ�true=�ɹ���false=ʧ��
//-----------------------------------------------------------------------------
bool_t DFFSD_rename_item(struct file_rsc *fp,char *newname)
{
    struct st_DBX_device_tag *DBX_device_tag;
    struct fdt_info FDT_item;
    struct st_DBX_flash_tag *DBX_flash_tag;
    uint32_t name_len;
    uint32_t FDT_item_no;
    if(fp == NULL)
        return false;

    DBX_device_tag = (struct st_DBX_device_tag *)(fp->home_DBX->private_tag);
    DBX_flash_tag = (struct st_DBX_flash_tag *)DBX_device_tag->DBX_medium_tag;
    FDT_item_no = (uint32_t)fp->file_medium_tag;
    __DFFSD_read_FDT_item(DBX_flash_tag,FDT_item_no,&FDT_item);
    //fp->name���ļ�ϵͳģ���ṩ�ģ������ֵĳ��ȱ���Ӧ���ǺϷ��ģ�����fp��Ϊ
    //һ����Դ��㣬�Ǳ�¶�������µģ��п��ܱ����޸ģ��ʲ���ʹ��strlen��
    name_len = strnlen(fp->name,cn_flash_file_name_limit+1);
    if(name_len <= cn_flash_file_name_limit)  //�ļ������ֲ�����cn_flash_file_name_limit
        strcpy(FDT_item.name,newname);
    else
    {

        memcpy(FDT_item.name,newname,cn_flash_file_name_limit);
        FDT_item.name[cn_flash_file_name_limit] = '\0';
    }
    __DFFSD_write_FDT_item(DBX_flash_tag,FDT_item_no,&FDT_item);
    return true;
}

//----��Ⲣ����FDT��-----------------------------------------------------------
//���ܣ�����ڴ�����ɾ���ļ��Ĺ����жϵ磬�����ܵ���FDT�������ڲ�����������ѣ�
//      ��������Ⲣ�޸�֮
//������DBX_device_tag�����������ļ���ָ�룬ͨ�ýṹ����flashר�á�
//���أ�true=������Ļ��߳ɹ����ģ�false=�д����޸�ʧ��
//-----------------------------------------------------------------------------
bool_t __DFFSD_repair_FDT(struct st_DBX_flash_tag *DBX_flash_tag)
{
    return true;
}

//----��ѯĿ¼��ߴ�-----------------------------------------------------------
//���ܣ���ѯһ���ļ����Ŀ¼��ߴ磬���ֽڼ��㡣��Ӧ�ó�����Ҫ��ȡ����Ŀ¼��ʱ��
//      �������ñ���������Ŀ¼��ߴ磬Ȼ����ܷ����ڴ档
//������DBX_device_tag�����������ļ���ָ�룬ͨ�ýṹ����flashר�á�
//���أ�Ŀ¼��ߴ�
//-----------------------------------------------------------------------------
uint32_t DFFSD_check_FDT_size(struct st_DBX_device_tag *DBX_device_tag)
{
    struct st_DBX_flash_tag *DBX_flash_tag;
    struct flash_chip *chip;
    uint32_t result,block_no,block_no_next;
    if(DBX_device_tag == NULL)
        return 0;
    DBX_flash_tag = (struct st_DBX_flash_tag*)DBX_device_tag->DBX_medium_tag;
    chip = DBX_flash_tag->chip;
    block_no_next = DBX_flash_tag->DDR_FDSB;
    result = 0;
    do
    {
        block_no = block_no_next;

       	if(DBX_flash_tag->DDR_MAT[block_no].attr == cn_FDT_block)
        	result ++;
        block_no_next = DBX_flash_tag->DDR_MAT[block_no].next;
    }while(block_no != block_no_next);
    return result * chip->block_size;
}

//----��Ŀ¼��-----------------------------------------------------------------
//���ܣ�����һ���ļ��������Ŀ¼����ԭʼ���ݶ�������������
//������DBX_device_tag�����������ļ���ָ�룬ͨ�ýṹ����flashר�á�
//      buf�������ȡ�����ݵĻ�����ָ�룬�û�����ǰ�������ſռ�
//���أ���
//-----------------------------------------------------------------------------
void DFFSD_read_FDT(struct st_DBX_device_tag *DBX_device_tag,uint8_t *buf)
{
    struct st_DBX_flash_tag *DBX_flash_tag;
    struct flash_chip *chip;
    uint32_t block_no,block_no_next;
    uint32_t completed = 0;
    if((DBX_device_tag == NULL) || (buf == NULL))
        return;
    DBX_flash_tag = (struct st_DBX_flash_tag*)DBX_device_tag->DBX_medium_tag;
    chip = DBX_flash_tag->chip;
    block_no_next = DBX_flash_tag->DDR_FDSB;
    do
    {
        block_no = block_no_next;
        chip->read_data_with_ecc(block_no + DBX_flash_tag->start_block,0,
                                 buf+completed,chip->block_size);
        block_no_next = DBX_flash_tag->DDR_MAT[block_no].next;
        completed += chip->block_size;
    }while(block_no != block_no_next);
    return ;
}

//----��ѯ�ļ������-----------------------------------------------------------
//����: �����ļ����ܿռ䣬��Ч�ռ䣬���пռ���ֽ���
//����:
//����: ��
//-----------------------------------------------------------------------------
void DFFSD_check_DBX(struct st_DBX_device_tag *DBX_device_tag,
                     sint64_t *sum_size,sint64_t *valid_size,sint64_t *free_size)
{
    struct st_DBX_flash_tag *DBX_flash_tag;
    struct flash_chip *chip;
    if(DBX_device_tag == NULL)
    {
        if(sum_size != NULL)
            *sum_size = 0;
        if(valid_size != NULL)
            *valid_size = 0;
        if(free_size != NULL)
            *free_size = 0;
    }else
    {
        DBX_flash_tag =(struct st_DBX_flash_tag*)DBX_device_tag->DBX_medium_tag;
        chip = DBX_flash_tag->chip;
        if(sum_size != NULL)
            *sum_size = DBX_flash_tag->block_sum * chip->block_size;
        if(valid_size != NULL)
            *valid_size = DBX_flash_tag->valid_sum * chip->block_size;
        if(free_size != NULL)
            *free_size = DBX_flash_tag->free_sum * chip->block_size;
    }
}
//----���DBX_device_tag-------------------------------------------------------
//����: ���DBX_device_tag
//������DBX_device_tag�����������ļ���ָ�룬ͨ�ýṹ����flashר�á�
//      name���ļ�����
//����: ��
//-----------------------------------------------------------------------------
void __DFFSD_fill_DBX_device_tag(struct st_DBX_device_tag *DBX_device_tag,
                                 char *name)
{
    DBX_device_tag->format = DFFSD_format_DBX;
    DBX_device_tag->write = DFFSD_write_file;
    DBX_device_tag->read = DFFSD_read_file;
    DBX_device_tag->flush = DFFSD_flush_file;
    DBX_device_tag->query_file_stocks = DFFSD_query_file_stocks;
    DBX_device_tag->query_file_cubage = DFFSD_query_file_cubage;
    DBX_device_tag->check_DBX = DFFSD_check_DBX;
    DBX_device_tag->set_file_size = __DFFSD_set_file_size;
    DBX_device_tag->seek_file = DFFSD_seek_file;
    DBX_device_tag->create_item = DFFSD_create_file;
//    DBX_device_tag->move_file= DFFSD_move_file; 
    DBX_device_tag->remove_item = DFFSD_remove_file;
    DBX_device_tag->open_item = DFFSD_open_item;
    DBX_device_tag->close_item = DFFSD_close_item;
    DBX_device_tag->lookfor_item = DFFSD_lookfor_item;
    DBX_device_tag->rename_item = DFFSD_rename_item;
	DBX_device_tag->item_traversal_son = DFFSD_item_traversal_son;
    DBX_device_tag->check_fdt_size = DFFSD_check_FDT_size;
    DBX_device_tag->read_fdt = DFFSD_read_FDT;
    DBX_device_tag->check_folder = DFFSD_check_folder;
    DBX_device_tag->opened_sum = 0;
    //name�϶��Ǹ����ȺϷ����ַ���
    if(strlen(name) <= cn_flash_DBX_name_limit)
        strcpy(DBX_device_tag->name,name);  //���ļ�������
    else
    {
        memcpy(DBX_device_tag->name,name,cn_flash_DBX_name_limit);
        DBX_device_tag->name[cn_flash_DBX_name_limit] = '\0';
    }
}

//----DFFSDģ���ʼ��----------------------------------------------------------
//����: ������ϵͳ��Դ���������flashоƬ�����
//����: ��
//����: 1
//-----------------------------------------------------------------------------
ptu32_t module_init_DFFSD(ptu32_t para)
{
    //����Դ�����н���һ������㣬ϵͳ������оƬ��������������
    rsc_add_tree_root(&tg_flash_chip_root_rsc,sizeof(struct  rsc_node),
                        "flash chip");
    return 1;
}

//----ɨ��оƬ-----------------------------------------------------------------
//����: ����ʱɨ��оƬ��ʶ��оƬ�е��ļ��񣬲����ļ�����뵽ϵͳ�豸����
//      �г�Ϊ��fs���豸�����豸��
//����: chip����ɨ���оƬ
//      start_block_no��ɨ����ʼ��ţ�ǰ��Ŀ��Ǳ�����
//����: ��
//-----------------------------------------------------------------------------
void __DFFSD_scan_chip(struct flash_chip *chip,uint32_t start_block_no)
{
    uint32_t loop,table_size,DDR_blocks,restored_block;
    djy_handle_t fs_handle_right = NULL;
    struct st_DBX_flash_tag *DBX_flash_tag = NULL;
    struct st_DBX_device_tag *DBX_device_tag = NULL;
    struct DBX_semp_para semp_dbx;
    struct MDR_temp_record MDR_record;
    struct fdt_info FDT_item;

    chip->valid_sum = chip->block_sum - start_block_no;
    if(! __DFFSD_read_MDR(chip,&MDR_record))
    {//ϵͳ��һ���������϶�û�н����ļ��񡣹ʼ��ص�ʱ�򣬰�DFFSD_init_MDR�����ⲽ��ʼ��
        DFFSD_init_MDR(chip,start_block_no); //δ��ʼ����оƬ��Ĭ�����ó�ʼ��
        return ;
    }
    //���ļ�ϵͳ�豸�����ֽӿ�
    if((fs_handle_right = dev_open_right("fs",0)) == NULL)
        return ;
    for(loop=0; loop < cn_DBX_sum_max; loop++)   //��������ļ���
    {
        DBX_device_tag = NULL;
        DBX_flash_tag = NULL;
        if(!chip->MDR.DBX_created[loop])
            continue;
        //�����ļ����豸ר�����ݽṹ�ڴ棬�ýṹ��Ƕ�뵽���豸�ṹ��
        DBX_device_tag = (struct st_DBX_device_tag*)
                    m_malloc_gbl(sizeof(struct st_DBX_device_tag),0);
        if(DBX_device_tag == NULL)
            goto goto_exit_install_chip;
        //����flash�ļ�ϵͳר�����ݽṹ�ڴ棬�ýṹ��Ƕ�뵽�ļ����豸��
        DBX_flash_tag = (struct st_DBX_flash_tag*)
                    m_malloc_gbl(sizeof(struct st_DBX_flash_tag),0);
        if(DBX_flash_tag == NULL)
            goto goto_exit_install_chip;
        memset(DBX_flash_tag,0,sizeof(struct st_DBX_flash_tag));
        memset(DBX_device_tag,0,sizeof(struct st_DBX_device_tag));
        DBX_flash_tag->ART_position = NULL;
        DBX_flash_tag->ART_block_no = NULL;
        DBX_flash_tag->ART_times = NULL;
        DBX_flash_tag->writed_DDR_main = NULL;
        DBX_flash_tag->writed_DDR_bak = NULL;
        DBX_flash_tag->DDR_DBL = NULL;
        DBX_flash_tag->DDR_MAT = NULL;
        DBX_flash_tag->chip = chip;     //flash�ļ���洢������оƬ
        DBX_flash_tag->DBX_no = loop;   //���ļ�����оƬ�е����
        DBX_flash_tag->start_block = MDR_record.start_blocks[loop];
        DBX_flash_tag->PCRB_no = MDR_record.PCRB_block_no[loop]
                                    -DBX_flash_tag->start_block;
        DBX_flash_tag->DDR_main = MDR_record.DDR_main_block_no[loop]
                                    -DBX_flash_tag->start_block;
        DBX_flash_tag->DDR_bak = MDR_record.DDR_bak_block_no[loop]
                                    -DBX_flash_tag->start_block;
        DBX_flash_tag->block_sum = MDR_record.blocks_sum[loop];
        chip->valid_sum -= DBX_flash_tag->block_sum;

        //��亯��ָ����ļ�����
        __DFFSD_fill_DBX_device_tag(DBX_device_tag,MDR_record.name[loop]);
        //�ļ����豸�Ĵ洢ý��ָ��flash�ļ���洢��
        DBX_device_tag->DBX_medium_tag = (ptu32_t)DBX_flash_tag;

        DBX_device_tag->formatted = MDR_record.formatted[loop];
        //4+4+2=λ�ñ�4�ֽ�+��ű�4�ֽ�+������2�ֽ�
        table_size = DBX_flash_tag->block_sum * (4+4+2);
        //Ϊĥ��λ�ñ�����ڴ�
        DBX_flash_tag->ART_position = (uint32_t*)m_malloc_gbl(table_size,0);
        if(DBX_flash_tag->ART_position == NULL)
            goto goto_exit_install_chip;
        //Ϊĥ���ű�����ڴ�
        DBX_flash_tag->ART_block_no = DBX_flash_tag->ART_position
                                      + DBX_flash_tag->block_sum;
        //Ϊĥ�����������ڴ�
        DBX_flash_tag->ART_times = (uint16_t *)(DBX_flash_tag->ART_block_no
                                      + DBX_flash_tag->block_sum);
        //����DDR��ߴ�
        DBX_flash_tag->DDR_size = __DFFSD_calculate_DDR_size(DBX_flash_tag);
        //1��DDR��ռ�õĿ���
        DDR_blocks = (DBX_flash_tag->DDR_size
                            +chip->block_size-1)/chip->block_size;
        //��������DBL�������ڴ�
        DBX_flash_tag->DDR_DBL =(uint32_t*)m_malloc_gbl(DDR_blocks*8,0);
        if(DBX_flash_tag->DDR_DBL == NULL)
            goto goto_exit_install_chip;
        //����MAT�������ڴ�
        DBX_flash_tag->DDR_MAT = (struct MAT_table *)m_malloc_gbl(
                           DBX_flash_tag->block_sum*sizeof(struct MAT_table),0);
        if(DBX_flash_tag->DDR_MAT == NULL)
            goto goto_exit_install_chip;
        //����д���־
        DBX_flash_tag->writed_DDR_main = (bool_t*)m_malloc_gbl(
                                            DDR_blocks*sizeof(bool_t)*2,0);
        if(DBX_flash_tag->writed_DDR_main == NULL)
            goto goto_exit_install_chip;
        DBX_flash_tag->writed_DDR_bak=DBX_flash_tag->writed_DDR_main+DDR_blocks;

        if(DBX_device_tag->formatted) //����ļ����ʽ����
        {
            //����������лָ����ݣ�������Ҫ��ȡDDR,DDR���б�����ָ��鱣���Ŀ��ܡ�
            //����᲻�ɻָ����������Ϊ��ʹ���ļ����ƻ��������ļ���Ȼ���ã����
            //DDR���ƻ�������__read_DDR�����б������
            chip->restore_PCRB(DBX_flash_tag->PCRB_no+DBX_flash_tag->start_block,
                                &restored_block);
            if(__DFFSD_scan_DDR(DBX_flash_tag))
            {
                __DFFSD_sort_ART(DBX_flash_tag);
                __DFFSD_read_FDT_item(DBX_flash_tag,0,&FDT_item);
                __DFFSD_uasm_root_folder(DBX_flash_tag,&FDT_item);
            }else    //DDR������ļ�����Ҫ���¸�ʽ������ʹ��
                DBX_device_tag->formatted = false;
            if(restored_block < chip->block_sum)
            {
                if(DBX_flash_tag->DDR_MAT[restored_block].attr == cn_FDT_block)
                    __DFFSD_repair_FDT(DBX_flash_tag);
            }
        }
        semp_dbx.left = chip->left_semaphore;   //оƬ�������ź���
        semp_dbx.right = chip->right_semaphore; //оƬ�������ź���
        if(dev_ctrl_right(fs_handle_right,enum_fs_add_DBX,
                            (ptu32_t)DBX_device_tag,(ptu32_t)&semp_dbx)
                            == enum_fs_no_error)
        {
            continue;   //���ͷ��ļ����豸����ڴ棬ֱ�ӽ�����һѭ��
        }else
        {
            goto goto_exit_install_chip;
        }

        //����Ѿ���ʽ���ˣ�����Ŀ¼��file_medium_tag��������
        if(DBX_device_tag->formatted)
        {
            DBX_device_tag->opened_root->file_medium_tag = (ptu32_t)0;
        }        
    }
    //������������
    dev_close_right(fs_handle_right);     //�ر��ļ�ϵͳ�豸
    return ;
goto_exit_install_chip:
    dev_close_right(fs_handle_right);     //�ر��ļ�ϵͳ�豸
    if(DBX_flash_tag !=NULL)
    {
        if(DBX_flash_tag->writed_DDR_main != NULL)
            m_free(DBX_flash_tag->writed_DDR_main);
        if(DBX_flash_tag->DDR_MAT != NULL)
            m_free(DBX_flash_tag->DDR_MAT);
        if(DBX_flash_tag->DDR_DBL != NULL)
            m_free(DBX_flash_tag->DDR_DBL);
        if(DBX_flash_tag->ART_position != NULL)
            m_free(DBX_flash_tag->ART_position);
        m_free(DBX_flash_tag);
    }
    if(DBX_device_tag !=NULL)   m_free(DBX_device_tag);
    return ;
}

//----��װһ��оƬ------------------------------------------------------------
//����: ��оƬ���Ѿ���ʼ�����ļ���Ǽǵ��ļ�ϵͳ�У����ļ������δ��ʽ��
//����: chip������װ��оƬ
//      rev_blocks����оƬ����������
//����: �������ļ���������������0���ʾоƬ��δ��ʼ��
//----------------------------------------------------------------------------
bool_t DFFSD_install_chip(struct flash_chip *chip,char *name,uint32_t rev_blocks)
{
#if cn_MDR_size < cn_MDR_CDR_size + cn_MDR_DBX_size +cn_DBX_sum_max*3*8*2+8
    return false;  //������������MDR������������С��2����Ŀ��û�����塣
#endif

    if(chip == NULL)
        return false;
    chip->left_semaphore = semp_create(1,1,name);
    if(chip->left_semaphore == NULL)
        return false;
    if((chip->right_semaphore = semp_create(1,1,name))==NULL)
    {
        semp_delete(chip->left_semaphore);
        return false;
    }
    chip->block_buf = m_malloc_gbl(chip->block_size,0);  //����黺�����ڴ�
    if(chip->block_buf == NULL)
    {
        semp_delete(chip->right_semaphore);
        semp_delete(chip->left_semaphore);
        return false;
    }
    //����flashоƬ���뵽flashоƬ����Դ����£����ڶ���β
    rsc_add_son(&tg_flash_chip_root_rsc,&chip->chip_node,
                        sizeof(struct flash_chip),name);
    __DFFSD_scan_chip(chip,rev_blocks);
    return true;
}

bool_t get_file_block_no(char *fullname)
{
	struct file_rsc *fp;
    struct st_DBX_device_tag *DBX_device_tag;
    struct st_DBX_flash_tag *DBX_flash_tag;
    struct fdt_info FDT_item;
	uint32_t loop,next_block;
    
	fp = djyfs_fopen(fullname,"r");
    if(fp == NULL)
        return 0;
    DBX_device_tag = (struct st_DBX_device_tag *)(fp->home_DBX->private_tag);
    DBX_flash_tag = (struct st_DBX_flash_tag*)DBX_device_tag->DBX_medium_tag;
    __DFFSD_read_FDT_item(DBX_flash_tag,
                          (uint32_t)fp->file_medium_tag,&FDT_item);
    //���ļ���˵����ǰ����·����������
    if(FDT_item.mattr & cn_FS_ATTR_DIRECTORY)
        return 0;  
	loop = __pick_little_32bit(FDT_item.fstart_dson,0);
	djy_printf("\n0x%8x", loop);
    //djy_printf(fullname);
    //djy_printf("�е��ļ���ռ�õĿ��:\r\n˳����:");
	do
    {
        next_block = loop;
        loop = DBX_flash_tag->DDR_MAT[next_block].next;
        djy_printf(" 0x%8x", loop);
    }while(loop != next_block);
	djy_printf("\r\n");
	djyfs_fclose(fp);
	return true;    
}

//extern const u8 cs_gb2312_song_16[];
 void test_flash_file( void )
{
    struct flash_chip *chip;
    djyfs_file *fp,*fp1,*fp3,*fp4,*zk;
    struct rsc_node *chip_tree;
    u32  result = 0;
#if 1
    chip_tree = rsc_search_tree("flash chip");
    chip = (struct flash_chip *)rsc_get_son(chip_tree);
    result = DFFSD_create_DBX(chip,1000,"sys");
    djyfs_format(1,0,"sys");

    fp = djyfs_fopen("sys:\\test.dbx","w+");
    fp1 =djyfs_fopen("sys:\\test2.dbx","w+");
    fp3 =djyfs_fopen("sys:\\folder1\\test3.dbx","w+");
    fp4 =djyfs_fopen("sys:\\folder1\\test4.dbx","w+");
    zk = djyfs_fopen("sys:\\gb2312_1616","w+");
//    djyfs_fwrite(cs_gb2312_song_16,282016,1,zk);
#endif
}

#endif //#if ((cfg_djyfs == 1) && (cfg_run_mode != cn_mode_tiny) && (cfg_djyfs_flash == 1))
