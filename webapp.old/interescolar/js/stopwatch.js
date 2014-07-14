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

	function draw_arc(id_cvs, color, glow, arc_deg) {
		var cvs = $(id_cvs).get(0);
		var ctx = cvs.getContext("2d");
		ctx.clearRect(0, 0, cvs.width, cvs.height);
		ctx.beginPath();
		ctx.strokeStyle   = color;
		ctx.shadowBlur    = 10;
		ctx.shadowOffsetX = 0;
		ctx.shadowOffsetY = 0;
		ctx.shadowColor   = glow;

		ctx.arc(94, 94, 84, deg(0), deg(arc_deg));
		ctx.lineWidth = 12;
		ctx.stroke();
	}

	var button = document.getElementById("startStop")
	
	this.startStop = function() {
		if (active == true) {
			button.value = "Iniciar"
			active = false;
			sta_time = delta;
			clock.freeze();
		} else {
			button.value = "Detener"
			active = true;
			old_time = Date.now();
			clock.run();
		}
	}

	this.resetAndClear = function () {
		button.value = "Iniciar"
		
		values.msecs   = 0;
		values.seconds = 0;
		values.minutes = 0;
		values.hours   = 0;
		sta_time = 0;
		
		active = false;
		clock.freeze();
		clock.refresh();

		/* --- DELETE ME  --> */
		if (values.minutes >= 4) {
			values.minutesGlow = settings.minutesGlow;
		}
		/* <-- DELETE ME  --- */

		draw_arc("#canvas_seconds", values.secondsColor,
			values.secondsGlow, 360);
		draw_arc("#canvas_minutes", values.minutesColor,
			values.minutesGlow, 360);
	/*
		draw_arc("#canvas_hours", values.hoursColor,
			values.hoursGlow, 360);
	*/
	}

	var inter = null;
	var clock = {
		set: {
			seconds: function() {
				draw_arc("#canvas_seconds", values.secondsColor,
					values.secondsGlow, 6 * (values.seconds + 0.001 * values.msecs));

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
				draw_arc("#canvas_minutes", values.minutesColor,
					values.minutesGlow, 120 * values.minutes);

				$(".clock_minutes .val").text(values.minutes);
			},
			hours: function() {
			/*
				draw_arc("#canvas_hours", values.hoursGlow,
					values.hoursGlow, 15 * values.hours);
				$(".clock_hours .val").text(values.hours);
			*/
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
				values.hours   = 24;
				values.minutes =  0;
				values.seconds =  0;
				values.msecs   =  0;
				clock.freeze();
			}
	
			clock.refresh();
		},

		refresh: function() {
			/* --- DELETE ME  --> */
			if (values.minutes >= 3) {
				values.minutesGlow = values.hoursGlow;
			}
			/* <-- DELETE ME  --- */

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

	this.resetAndClear();

	if (values.autostart)
		this.startStop();
}