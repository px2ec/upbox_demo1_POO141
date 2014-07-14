function StopWatch(settings) {
	var values = settings;
	
	var active = values.active;
	var msec_inc = values.msec_inc;

	function deg(deg) {
		return (Math.PI/180) * deg - (Math.PI/180) * 90;
	}

	this.startStop = function() {
		if (active == 1) {
			active = 0;
			clock.freeze();
		} else {
			active = 1;
			clock.run();
		}
	}

	this.resetAndClear = function () {
		values.msecs   = 0;
		values.seconds = 0;
		values.minutes = 0;
		values.hours   = 0;
		values.days    = 0;

		active = 0;
		clock.freeze();
		clock.refresh();
	}

	var inter = null;
	var clock = {
		set: {
			seconds: function() {
				var cSec = $("#canvas_seconds").get(0);
				var ctx = cSec.getContext("2d");
				ctx.clearRect(0, 0, cSec.width, cSec.height);
				ctx.beginPath();
				ctx.strokeStyle = values.secondsColor;

				ctx.shadowBlur    = 10;
				ctx.shadowOffsetX = 0;
				ctx.shadowOffsetY = 0;
				ctx.shadowColor = values.secondsGlow;

				ctx.arc(95,95,80, deg(0), deg(6*values.seconds));
				ctx.lineWidth = 12;
				ctx.stroke();

				var caption = "";
				if (values.msecs == 0) {
					caption = values.seconds + ".000";
				} else if (values.msecs < 100) {
					caption = values.seconds + ".0" + values.msecs;
				} else {
					caption = values.seconds + "." + values.msecs;
				}
				$(".clock_seconds .val").text(caption);
			},
			minutes: function() {
				var cMin = $("#canvas_minutes").get(0);
				var ctx = cMin.getContext("2d");
				ctx.clearRect(0, 0, cMin.width, cMin.height);
				ctx.beginPath();
				ctx.strokeStyle = values.minutesColor;

				ctx.shadowBlur    = 10;
				ctx.shadowOffsetX = 0;
				ctx.shadowOffsetY = 0;
				ctx.shadowColor = values.minutesGlow;

				ctx.arc(95,95,80, deg(0), deg(6*values.minutes));
				ctx.lineWidth = 12;
				ctx.stroke();
				$(".clock_minutes .val").text(values.minutes);
			},
			hours: function() {
				var cHr = $("#canvas_hours").get(0);
				var ctx = cHr.getContext("2d");
				ctx.clearRect(0, 0, cHr.width, cHr.height);
				ctx.beginPath();
				ctx.strokeStyle = values.hoursColor;

				ctx.shadowBlur    = 10;
				ctx.shadowOffsetX = 0;
				ctx.shadowOffsetY = 0;
				ctx.shadowColor = values.hoursGlow;

				ctx.arc(95,95,80, deg(0), deg(15*values.hours));
				ctx.lineWidth = 12;
				ctx.stroke();
				$(".clock_hours .val").text(values.hours);
			},
			days: function() {
				var cdays = $("#canvas_days").get(0);
				var ctx = cdays.getContext("2d");
				ctx.clearRect(0, 0, cdays.width, cdays.height);
				ctx.beginPath();
				ctx.strokeStyle = values.daysColor;
				
				ctx.shadowBlur    = 10;
				ctx.shadowOffsetX = 0;
				ctx.shadowOffsetY = 0;
				ctx.shadowColor = values.daysGlow;
				
				ctx.arc(95,95,80, deg(0), deg((360/values.total)*(values.total - values.days)));
				ctx.lineWidth = 12;
				ctx.stroke();
				$(".clock_days .val").text(values.days);
			},
		},

		update: function() {
			if (values.msecs < 950) {
				values.msecs += msec_inc;
			} else {
				values.msecs = 0;
				if (values.seconds < 59 ) {
					values.seconds++;
				} else {
					values.seconds = 0;
					if (values.minutes < 59) {
						values.minutes++;
					} else {
						if (values.hours < 23) {
							values.hours++;
						} else {
							values.hours = 0;
							values.days++;
						}
					}
				}
			}
			
			clock.refresh();
		},

		refresh: function() {
			clock.set.seconds();
			clock.set.minutes();
			clock.set.hours();
			clock.set.days();
		},

		run: function() {
			inter = setInterval(clock.update, msec_inc);
		},

		freeze: function() {
			clearInterval(inter);
		}
	}

	clock.refresh();
	if (active == 1)
		clock.run();
}