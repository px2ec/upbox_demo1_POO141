function StopWatch(settings) {
	var values = settings;
	var active = false;

	var delta = 0;
	var sta_time = 0;
	var cur_time = 0;
	var old_time = 0;
	
	sta_time += values.hours   * 3600000;
	sta_time += values.minutes * 60000;
	sta_time += values.seconds * 1000;
	sta_time += values.msecs;

	function deg(deg) {
		return (Math.PI/180) * (deg -  90);
	}

	this.startStop = function() {
		if (active == true) {
			active = false;
			sta_time = delta;
			clock.freeze();
		} else {
			active = true;
			old_time = Date.now();
			clock.run();
		}
	}

	this.resetAndClear = function () {
		values.msecs   = 0;
		values.seconds = 0;
		values.minutes = 0;
		values.hours   = 0;
		sta_time = 0;
		
		active = false;
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

				var caption;
				if (values.msecs == 0) {
					caption = values.seconds + ".000";
				} else if (values.msecs < 10) {
					caption = values.seconds + ".00" + values.msecs;
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
		},

		update: function() {
			cur_time = Date.now();
			delta = sta_time + cur_time - old_time;

			values.msecs   = delta % 1000;
			values.seconds = Math.floor(delta / 1000) % 60;
			values.minutes = Math.floor(delta / 60000) % 60;
			values.hours   = Math.floor(delta / 3600000);

			if (values.hours >= 24) {
				values.hours = 24;
				clock.freeze();
			}
	
			clock.refresh();
		},

		refresh: function() {
			clock.set.seconds();
			clock.set.minutes();
			clock.set.hours();
		},

		run: function() {
			inter = setInterval(clock.update,
				Math.floor(1000/values.rfrate));
		},

		freeze: function() {
			clearInterval(inter);
		}
	}

	clock.refresh();
	if (values.autostart)
		this.startStop();
}