function getData(url, round) {
	var query = $.get(url);
	
	var msg = '\n';
	msg += '<img src="img/ajax-loading.gif"';
	msg += ' width="16" height="11"';
	msg += ' alt="">';
	msg += ' Actualizando...\n';
	$("#msgBox").html(msg);
	$("#msgBox").attr("style", "visibility: visible;");

	query.done(function(data, status) {
		var newRowsTp = '\n';
		var newRowsAp = '\n';

		var val = data.equipos;
		var roundToCheck;
		for (var i = 0; i < val.length; i++) {
			if (round == 1) roundToCheck = val[i][2];
			else roundToCheck = val[i][3];

			if (roundToCheck == 0) {
				var textValue = (val[i][4] < 1) ? '' : val[i][4];
				newRowsTp += '<tr>\n';
				newRowsTp += '  <td><a href="javascript:moveDown(' + val[i][0] + ')">Bajar</td>\n';
			//	newRowsTp += '  <td>' + textValue + '</td>\n';
				newRowsTp += '  <td>' + val[i][1] + '</td>\n';
				newRowsTp += '</tr>\n';
			} else {
				var newRowsApR = '';
				newRowsApR += '<tr>\n';
				newRowsApR += '  <td><a href="javascript:moveUp(' + val[i][0] + ')">Subir</td>\n';
				newRowsApR += '  <td>' + val[i][1] + '</td>\n';
				newRowsApR += '</tr>\n';
				newRowsApR += newRowsAp;
				newRowsAp = newRowsApR;
			}
		}

		$("#updateMeTp").html(newRowsTp);
		$("#updateMeAp").html(newRowsAp);
		$("#msgBox").attr("style", "visibility: hidden;");
		return true;
	});

	query.fail(function(data, status) {
		$("#msgBox").html("Error al actualizar!")
		$("#msgBox").attr("style", "visibility: visible;");
		return false;
	});
}

function updateValues(settings)
{
	var running = false;
	var round = settings.round;
	this.startStop = function() {
		var link = document.getElementById('updLink');
		if (running == false) {
			link.innerHTML = "Detener";
			running = true;
			action.run();
		} else {
			link.innerHTML = "Actualizar";
			running = false;
			action.freeze();
		}
	}

	this.getRound = function() {
		return round;
	}

	this.chRound = function(new_round) {
		round = new_round;
	}

	var inter;
	var action = {
		refresh: function() {
			getData(settings.url, round);
		},

		run: function() {
			action.refresh();
			inter = setInterval(action.refresh,
				settings.rfrate);
		},
		
		freeze: function() {
			clearInterval(inter);
		},
	};

	if (!settings.autorun) {
		return false;
	}

	this.startStop();
	return true;
}