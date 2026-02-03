#include <linux/usb.h>
#include <linux/module.h>

/*
constructor __init
destructor __exit
*/

static struct usb_device* device;


static struct usb_device_id skel_table[] = {
    {USB_DEVICE(0x0e8d, 0x201c)},           // fetched from dmesg
    {}};
MODULE_DEVICE_TABLE(usb, skel_table);

static int skel_probe(struct usb_interface* interface, const struct usb_device_id* id)
{
    struct usb_host_interface* iface;
    struct usb_endpoint_descriptor* endpointdesc;

    int i;
    iface = interface->cur_altsetting;
    printk(KERN_INFO "Pendrive interface %d now probed: {%04X:%04X}\n",
               iface->desc.bInterfaceNumber,
            id->idVendor, id->idProduct);

    printk(KERN_INFO "ID->bNumEndpoints: %02X\n", iface->desc.bNumEndpoints);
    printk(KERN_INFO "ID->bInterfaceClass: %02X\n", iface->desc.bInterfaceClass);

    for(i=0; i < iface->desc.bNumEndpoints; i++)
    {
        endpointdesc = &iface->endpoint[i].desc;
        printk(KERN_INFO "ED[%d]->bENdpointAddress: 0X%02x\n", i, endpointdesc->bEndpointAddress);
        printk(KERN_INFO "ED[%d]->bmAttributes: 0x%02X\n",
                i, endpointdesc->bmAttributes);
        printk(KERN_INFO "ED[%d]->wMaxPacketSize: 0x%04X (%d)\n",
                i, endpointdesc->wMaxPacketSize,
                endpointdesc->wMaxPacketSize);

    }
    device = interface_to_usbdev(interface);
    return 0;
}


static void skel_disconnect(struct usb_interface* interface)
{
    usb_put_dev(device);
    printk(KERN_INFO "Pen drive removed\n");
}

static struct usb_driver skel_driver  =
{
    .name = "usb_driver",
    .probe = skel_probe,
    .disconnect = skel_disconnect,
    .id_table = skel_table,
    .supports_autosuspend = 1,
};


static int __init usb_skel_init(void)
{
    int result;
    result = usb_register(&skel_driver);
    if(result < 0)
    {
        pr_err("USB Register failed with %s\n", skel_driver.name);
        return -1;
    }
    printk(KERN_INFO "Module is initialised\n");
    return 0;
}

module_init(usb_skel_init);

static void __exit usb_skel_exit(void)
{
    printk(KERN_INFO "Module is exited\n");
}

module_exit(usb_skel_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aditya Sakare");
MODULE_DESCRIPTION("USB Driver");
