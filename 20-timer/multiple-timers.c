#include <linux/module.h>
#include <linux/timer.h>

struct timer_list mytimer;

#define MYTIMER_TIMEOUT_SECS	10

struct mytimer_data {
	char *name;
	int interval;
	struct timer_list timer;
};

struct mytimer_data data[2] = {
	{
	 .name = "foo",
	 .interval = 2,
	  },
	{
	 .name = "bar",
	 .interval = 3,
	  },
};

static void mytimer_fn(struct timer_list *timer)
{
	struct mytimer_data *data =
	    container_of(timer, struct mytimer_data, timer);

	pr_info("%s: %d secs passed.\n",
	       data->name, data->interval);

	mod_timer(&data->timer, jiffies + data->interval * HZ);
}

static int mymodule_init(void)
{
	int i;

	for (i = 0; i < 2; i++) {
		struct mytimer_data *d = &data[i];
		timer_setup(&d->timer, mytimer_fn, 0);
		d->timer.expires = jiffies + data[i].interval * HZ;
		add_timer(&d->timer);
	}

	return 0;
}

static void mymodule_exit(void)
{
	int i;

	for (i = 0; i < 2; i++) {
		del_timer(&data[i].timer);
	}
}

module_init(mymodule_init);
module_exit(mymodule_exit);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Satoru Takeuchi <satoru.takeuchi@gmail.com>");
MODULE_DESCRIPTION("timer kernel module: oneshot timer");
