/*global require:false*/
/*global PDFObject:false*/
/*global Modernizr:false*/
/*global confirm:false*/

(function() {
	
if (!Modernizr.cssgradients) {
	require(["jquery"], function($) {
		$(function() {
			$("body").html("<h1>SJTU Online Judge</h1><p>Your Web Browser is too old and is not supported. Please upgrade to latest Chrome/Firefox/Safari, thank you</p><p>请升级您的浏览器。我们推荐最新的Chrome、Firefox或者Safari</p>");
		});
	});
	return;
}

require.config({
	urlArgs : "bust=" + (new Date().getTime())
});

require([
    "jquery",
    "judge/controllers/StandingsController",
    "judge/NotificationService",
	"judge/controllers/EditProblemsController",
	"judge/controllers/ProblemQuickSearchController",
    "jquery.mobile"],
function(
    $,
    StandingsController,
    notificationService,
	EditProblemsController,
	ProblemQuickSearchController
) {
    /**
     * Start the notification service
     */
    notificationService.start();
    /**
     * Common functions initialization
     */
    $(document).on("click", "a[data-need-confirm='true']", function() {
        var prompt = $(this).data("confirm-text") || "Are you sure?";
        return confirm(prompt);
    });
	$(document).on("pageinit", function() {
		// Embed PDF files
		$(this).find(".pdf-container").each(function() {
			var url = $(this).data("url");
			var id = "pdf-" + Math.random();
			$(this).attr("id", id);
			new PDFObject({
				url : url,
				height : "600px"
			}).embed(id);
		});
	});
	/**
	 * Initialize Standings
	 */
	$(document).on("pageshow", ".page-standings", function() {
		var container = $(this).find(".standings-container");
		var controller = new StandingsController({container: container});
		controller.test = 1;
	});
    $(document).on("pageshow", function() {
        var widget = $(this).find(".js-contest-current-time");
        if (widget.length) {
            var url = widget.data("url");
            var event = null;
            var update = function() {
                $.get(url, function(data) {
                    widget.html(data);
                    event = setTimeout(update, 10000);
                });
            };
            update();
        }
        $(document).one("pagehide", function() {
            if (event) {
                clearTimeout(event);
            }
        });
    });
	$(document).on("pageshow", function() {
		var $this = $(this);
		/**
		 * Submission Status Update Service
		 * will search the document and register a handler for all $(".js-widget-judgement")
		 */
		if ($this.find(".js-service-submission-status-update").length) {
			var t = $this.find(".js-service-submission-status-update");
			var url = t.data("url");
			var interval = t.data("interval");
			require(["judge/SubmissionStatusUpdateService", "judge/utils"], function(service, utils) {
				service.setUrl(url);
				if (interval) {
					service.setPollingInterval(interval);
				}
				$(".js-widget-judgement").each(function() {
					var pk = $(this).data("pk");
					var dom = $(this);
					service.registerHandler(pk, function(status) {
						if (status[0] === "!") {
							status = status.substr(1);
							service.unregisterHandler(pk);
							dom.removeClass("verdict-waiting");
							dom.addClass("verdict-" + utils.slugify(status).toLowerCase());
						}
						dom.html(status);
					});
				});
				service.start();
				$(document).one("pagehide", function() {
					service.stop();
				});
			});
		}
		/**
		 * Edit Problem Widget
		 */
		$this.find(".js-widget-edit-contest-problems").each(function() {
			var controller = new EditProblemsController({
				container: this,
				apiUrl: $(this).data("api-url")
			});
			controller.initialize();
			$this.find(".js-widget-problem-quick-search").on("click", "li", function() {
				var info = $(this).data("problemInfo");
				controller.addProblem(info.id, info.title);
			});
		});
		$this.find(".js-widget-problem-quick-search").each(function() {
			var controller = new ProblemQuickSearchController({
				container: this,
				apiUrl: $(this).data("api-url")
			});
			controller.initialize();
		});
	});
    /**
     * Parse statistic info for test case result
     */
    $(document).on("pageshow", function() {
        $(this).find(".js-parse-submission-stat").each(function() {
            try {
                var json = JSON.parse($(this).html());
                $(this).html("Time: " + json.time.toFixed(2));
            } catch (e) {}
        });
    });
	$(".ui-page").trigger("pageinit");
	$(".ui-page").trigger("pageshow");
});
})();
