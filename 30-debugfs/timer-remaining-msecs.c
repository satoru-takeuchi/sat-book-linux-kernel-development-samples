#include <linux/module.h>
#include <linux/debugfs.h>

static struct dentry *testfile;
static char testbuf[128];

struct timer_list mytimer;

#define MYTIMER_TIMEOUT_SECS	((unsigned long)100)

static void mytimer_fn(struct timer_list *timer)
{
	pr_info("%lu secs passed.\n", MYTIMER_TIMEOUT_SECS);
}

static ssize_t mytimer_remaining_msecs_read(struct file *f,
					    char __user *buf, size_t len,
					    loff_t *ppos)
{
	unsigned long diff_msecs, now = jiffies;

	if (time_after(mytimer.expires, now))
		diff_msecs = (mytimer.expires - now) * 1000 / HZ;
	else
		diff_msecs = 0;

	snprintf(testbuf, sizeof(testbuf), "%lu\n", diff_msecs);
	return simple_read_from_buffer(buf, len, ppos, testbuf,
				       strlen(testbuf));
}

static struct file_operations test_fops = {
	.owner = THIS_MODULE,
	.read = mytimer_remaining_msecs_read,
};

static int mymodule_init(void)
{
	pr_info("Hello world!\n");
	timer_setup(&mytimer, mytimer_fn, 0);
	mytimer.expires = jiffies + MYTIMER_TIMEOUT_SECS * HZ;
	add_timer(&mytimer);

	testfile =
	    debugfs_create_file("mytimer-remaining-msecs", 0400, NULL,
				NULL, &test_fops);
	if (!testfile)
		return -ENOMEM;

	return 0;
}

static void mymodule_exit(void)
{
	debugfs_remove(testfile);
	del_timer(&mytimer);
}

module_init(mymodule_init);
module_exit(mymodule_exit);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Satoru Takeuchi <satoru.takeuchi@gmail.com>");
MODULE_DESCRIPTION("A simple example of debugfs");
