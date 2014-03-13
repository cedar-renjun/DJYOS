mcpu设为926e，编译器报错。
默认输出格式改为bin格式，文件名为*.bin。
哪里设定输出.map文件？
配置中malloc块尺寸后缀0的个数由工具定义。
定义栈段时，属性应该是aw
mmu_disable和mmu_enable函数中，去掉跟2410相关的内容。
release 默认要生成map文件。
data段和text段要分开。
ptu32_t module_init_FAT32返回值类型更改，原为void
修正djyos.c中的一个bug，在__djy_schedule函数中增加一行：
    int_cut_asyn_signal();
void *djy_get_event_para(u32 *time)函数增加time参数，用于返回时间。
现在build前不自动存盘，可否在插件中把build和存盘操作关联起来？
调stm32时，遇到malloc不返回的情况，pagesize = 32bytes，堆大约03c0000。改了m_free后系统可运行了，但不显示了。改成64bytes就正常。--已解决
新建窗口前，应先重绘一下，否则blend窗口积累的移动，可能失去。
显示文本时，如果坐标在窗口外，可能导致死机--林谦，要查一下。
待解决的问题：当文件柜不需要ecc校验时，会导致fdt表也没有ecc校验，特别是，查是否需擦除时不用ecc，但写的时候又用了ecc，导致严重出错。
DFFSD_item_traversal_son函数中current_file的内存管理，须好好整一下。