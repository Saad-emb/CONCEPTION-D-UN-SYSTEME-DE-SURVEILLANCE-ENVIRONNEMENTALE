#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif


static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x92997ed8, "_printk" },
	{ 0x610d80ea, "pwm_apply_state" },
	{ 0x4deedada, "pwm_free" },
	{ 0x43dd1c15, "cdev_del" },
	{ 0x54ae6ab6, "device_destroy" },
	{ 0x7391ca5d, "class_destroy" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x8da6585d, "__stack_chk_fail" },
	{ 0x6cbbfc54, "__arch_copy_to_user" },
	{ 0x12a4e128, "__arch_copy_from_user" },
	{ 0xdcb764ad, "memset" },
	{ 0x2505bf18, "kstrtol_from_user" },
	{ 0x98cf60b3, "strlen" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x7fb98451, "cdev_init" },
	{ 0x91128fc8, "cdev_add" },
	{ 0x8d30dba0, "__class_create" },
	{ 0xbf3f457f, "device_create" },
	{ 0x7d7acbec, "pwm_request" },
	{ 0xf9a482f9, "msleep" },
	{ 0x954a6358, "param_ops_int" },
	{ 0x8f80e6e5, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "81DBCBB8FCED7CA62A90600");
