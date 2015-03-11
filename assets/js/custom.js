/*var editor = CodeMirror.fromTextArea(document.getElementById("footer_custom_code_content"), {
	//mode: 'application/x-httpd-php',
	mode: 'css',
	lineNumbers: true,
});*/

(function($){
	
	$('select[name^="fcc_logic_value_selection"]').select2({
		placeholder: 'All',
		tags: true,
		theme: 'classic',/*,
		ajax: {
			url: ajaxurl,
			dataType: "json",
			type: "POST",
			delay: 250,
			data: function( params ) {
				console.log(params.term);
				return {
					qs: params.term,
					action: 'my_action'
				};
			},
			processResults: function( data, page ) {
				return {
					results: data.items
				};
			},
			cache: false
		}*/
	});

	$('select[name^="fcc_logic_type_selection"]').each(function(){
		var $type = $(this);
		var type = $type.val();
		var counter = $(this).attr('id').split('_').pop();
		var $selection = $('#fcc_logic_value_selection_' + counter);
		
		fillSelectionDropdown($, $type);

		$type.change(function(){
			fillSelectionDropdown($, $type);
		});
	});

})(jQuery);

function fillSelectionDropdown($, $type) {
	var type = $type.val();
	var counter = $type.attr('id').split('_').pop();
	var $selection = $('#fcc_logic_value_selection_' + counter);

	$selection.val('');

	console.log(type);
	$.ajax({
		url: ajaxurl,
		type: "POST",
		async: false,
		data: {
			action: 'fcc_logic_action',
			fcc_type: type
		}
	}).done(function(data){
		var options = '';
		$($.parseJSON(data)).each(function(idx, val){
			options = options + '<option value="'+val.id+'">'+val.text+'</option>';
		});
		$selection.html(options);
	});
}