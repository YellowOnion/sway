#include <strings.h>
#include "sway/commands.h"
#include "sway/config.h"
#include "sway/tree/view.h"

struct cmd_results *cmd_max_cursor_latency(int argc, char **argv) {
	if (!argc) {
		return cmd_results_new(CMD_INVALID, "Missing max cursor latency argument.");
	}

	int max_cursor_latency;
	if (!strcmp(*argv, "off")) {
		max_cursor_latency = 0;
	} else {
		char *end;
		max_cursor_latency = strtol(*argv, &end, 10);
		if (*end || max_cursor_latency <= 0) {
			return cmd_results_new(CMD_INVALID, "Invalid max cursor latency.");
		}
	}

	struct sway_container *container = config->handler_context.container;
	if (!container || !container->view) {
		return cmd_results_new(CMD_INVALID,
				"Only views can have a max_cursor_latency");
	}

	struct sway_view *view = container->view;
	view->max_cursor_latency = max_cursor_latency;

	return cmd_results_new(CMD_SUCCESS, NULL);
}
