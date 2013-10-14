
$(document).ready(function()
{
	$('head').append('<link rel="stylesheet" href="/sys/css/devbar.css" />');
	$('body').append('<div id="_sys_devbar">\
		<div id="_sys_devbar_version" title="Version de WebCpp"></div>\
		<div id="_sys_devbar_location" title="Module, contrôleur et action">\
			<span id="_sys_devbar_location_module"></span>\
			<span id="_sys_devbar_location_controller"></span>\
			<span id="_sys_devbar_location_action"></span></div>\
		<div id="_sys_devbar_route" title="Route"></div>\
		<div id="_sys_devbar_view" title="Vue"></div>\
		<div id="_sys_devbar_execTime" title="Temps de génération total">\
			<span id="_sys_devbar_execTime_total">0</span> ms\
			<div id="_sys_devbar_execTime_tooltip">\
				<table>\
					<tr>\
						<td class="label">Système :</td>\
						<td id="_sys_devbar_execTime_system"></td>\
					</tr>\
					<tr><td height="5" colspan="2"></td></tr>\
					<tr>\
						<td class="label">Utilisateur :</td>\
						<td id="_sys_devbar_execTime_user"></td>\
					</tr>\
					<tr>\
						<td class="label" style="font-size:0.8em;padding-left:10px">Templates :</td>\
						<td id="_sys_devbar_execTime_templates" style="font-size:0.8em"></td>\
					</tr>\
					<tr>\
						<td class="label" style="font-size:0.8em;padding-left:10px">SQL :</td>\
						<td id="_sys_devbar_execTime_database" style="font-size:0.8em"></td>\
					</tr>\
					<tr><td height="5" colspan="2"></td></tr>\
					<tr style="border-top: 1px solid white;">\
						<td class="label">Total :</td>\
						<td id="_sys_devbar_execTime_total2"></td>\
					</tr>\
				</table>\
			</div>\
		</div>\
		<div id="_sys_devbar_database" title="Nombre de requêtes SQL">\
			<span id="_sys_devbar_database_requestsCount">0</span>\
			<span id="_sys_devbar_database_execTime">(0 ms)</span>\
		</div>\
		<div id="_sys_devbar_close" title="Fermer"></div>\
	</div>');
	
	$('#_sys_devbar_close').click(function()
	{
		$('#_sys_devbar').fadeOut('fast', function(){ $(this).remove(); });
	});
	
	$('#_sys_devbar_execTime').mouseenter(function(){ $('#_sys_devbar_execTime_tooltip').fadeIn(); });
	$('#_sys_devbar_execTime').mouseleave(function(){ $('#_sys_devbar_execTime_tooltip').fadeOut(); });
	
	$.ajax({
		url: '/sys/profile',
		data: 'id='+_sys_profileId,
		dataType: 'json',
		success: function(datas)
		{
			$('#_sys_devbar_version').html(datas.webcppVersion);
			
			$('#_sys_devbar_route').html(datas.route);
			$('#_sys_devbar_view').html(datas.view);
			
			$('#_sys_devbar_execTime_total').html((Math.round(datas.execTime.total * 1000.0 * 1000.0)/1000.0).toLocaleString());
			$('#_sys_devbar_execTime_system').html((Math.round(datas.execTime.system * 1000.0 * 1000.0)/1000.0).toLocaleString() + ' ms');
			$('#_sys_devbar_execTime_user').html((Math.round( (datas.execTime.total - datas.execTime.system) * 1000.0 * 1000.0)/1000.0).toLocaleString() + ' ms');
			$('#_sys_devbar_execTime_templates').html((Math.round(datas.execTime.templates * 1000.0 * 1000.0)/1000.0).toLocaleString() + ' ms');
			$('#_sys_devbar_execTime_database').html((Math.round(datas.execTime.sql * 1000.0 * 1000.0)/1000.0).toLocaleString() + ' ms');
			$('#_sys_devbar_execTime_total2').html((Math.round(datas.execTime.total * 1000.0 * 1000.0)/1000.0).toLocaleString() + ' ms');
			
			$('#_sys_devbar_database_requestsCount').html(datas.sqlQueryCount);
			$('#_sys_devbar_database_execTime').html('('+(Math.round(datas.execTime.sql * 1000.0 * 1000.0)/1000.0).toLocaleString() + ' ms)');
		},
		error: function(xhr, status, error)
		{
			alert('Failed to get profile informations: '+error);
			$('#_sys_devbar').fadeOut('fast', function(){ $(this).remove(); });
		}
	});
});