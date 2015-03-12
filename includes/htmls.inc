<?php 
/**
 *
 */
function custom_code_metabox_content_html( $post ) 
{
	$content = get_post_meta( $post->ID, '_footer_custom_code_content', true );

	?>
	<div class="codemirror pritify">
		<textarea id="footer_custom_code_content" name="footer_custom_code_content" rows="15" style="width:100%;overflow:auto;"><?php echo $content;?></textarea>
	</div>
	<?php
}

/**
 *	
 */
function custom_code_metabox_types_html( $post ) { 

	$type = get_post_meta( $post->ID, '_footer_custom_code_type', true );

	if( trim($type) == '' )
	{
		$type = 'css';
	}

	?>
	<div id="post-formats-select">
		<input type="radio" name="footer_custom_code_type" id="footer_custom_code_type_css" value="css" <?php echo $type=='css'?'checked="checked"':'';?> />
		<label for="footer_custom_code_type_css">CSS</label>
		<br />
		<input type="radio" name="footer_custom_code_type" id="footer_custom_code_type_js" value="js" <?php echo $type=='js'?'checked="checked"':'';?> />
		<label for="footer_custom_code_type_js">Javascript</label>
		<br />
		<input type="radio" name="footer_custom_code_type" id="footer_custom_code_type_php" value="php" <?php echo $type=='php'?'checked="checked"':'';?> />
		<label for="footer_custom_code_type_php">PHP</label>
		<br />
	</div>		
	<?php 
}

/**
 *
 */
function custom_code_metabox_placement_html( $post ) 
{

	$placement = get_post_meta( $post->ID, '_footer_custom_code_placement', true );

	if( trim($placement) == '' )
	{
		$placement = 'inline';
	}

	$priority = get_post_meta( $post->ID, '_footer_custom_code_priority', true );

	if( trim($priority) == '' )
	{
		$priority = '0';
	}

	?>
	<div id="post-formats-select">
		<input type="radio" name="footer_custom_code_placement" id="footer_custom_code_placement_inline" value="inline" <?php echo $placement=='inline'?'checked="checked"':'';?> />
		<label for="footer_custom_code_placement_inline">Inline Script</label>
		<br />
		<input type="radio" name="footer_custom_code_placement" id="footer_custom_code_placement_external" value="external" <?php echo $placement=='external'?'checked="checked"':'';?> />
		<label for="footer_custom_code_placement_external">External File</label>
		<br /><br />
		<label for="footer_custom_code_priority">Periority </label> 
		<input type="number" name="footer_custom_code_priority" id="footer_custom_code_priority" value="<?php echo $priority;?>" size="5" />
		<br />
	</div>
		
	<?php
}

/**
 *
 */
function custom_code_metabox_logic_html( $post ) 
{

	$apply_only_if = get_post_meta( $post->ID, '_fcc_apply_only_if', true );
	$fcc_logics = unserialize( get_post_meta( $post->ID, '_footer_custom_code_logics', true ) );
	$logics = unserialize( get_post_meta( $post->ID, '_footer_custom_code_logics', true ) );

	$logic_rows = '';
	if( isset($fcc_logics['fcc_logic_type_selection']) && count( $fcc_logics['fcc_logic_type_selection'] ) > 0 )
	{
		// echo '<pre>'.print_r($fcc_logics,true).'</pre>';
		for ($i=0; $i < count( $fcc_logics['fcc_logic_type_selection'] ); $i++) { 
			if( isset($fcc_logics['ffc_logic_condition'][$i-1]) && $fcc_logics['ffc_logic_condition'][$i-1] == 'or' )
			{
				$logic_rows .= '<p> <input type="button" name="" id="" value="or" class="button" /> </p>';
			}
			$selected = 
			$logic_rows .= '<p id="fcc_logic_row_'.$i.'">
								'._build_type_selection_dropdown_html( $logics, $i ).'
								'._build_operator_selection_dropdown_html( $logics, $i ).'
								'._build_selection_selection_dropdown_html( $logics, $i ).'
								
								<input type="button" name="fcc_logic_button_and" id="fcc_logic_button_and" class="button" value="and" />
							</p>';
		}

	}
	else
	{
		$logic_rows .= '<p id="fcc_logic_row_0">
						'._build_type_selection_dropdown_html( $logics, 0 ).'
						'._build_operator_selection_dropdown_html( $logics, 0 ).'
						'._build_selection_selection_dropdown_html( $logics, 0 ).'
						<input type="button" name="fcc_logic_button_and" id="fcc_logic_button_and" class="button" value="and" />
					</p>';
	}
	$logic_rows .= '<p> <input type="button" name="" id="" value="or" class="button" /> </p>';
	
	?>
	<div id="post-formats-select">
		<label for="fcc_apply_only_if">
			<input type="checkbox" id="fcc_apply_only_if" name="fcc_apply_only_if" value="1" <?php echo $apply_only_if==1?'checked="checked"':''; ?> >
			 Apply Only If:
		</label>
		<div id="ffc_logic_rows_div">
			<?php echo $logic_rows;?>
		</div>
	</div>
	
	<?php
}

/**
 *
 */
function _build_type_selection_dropdown_html( $logics, $counter = 0 ) 
{
	$dropdown_array = _build_type_selection_dropdown_array();

	$options = '';

	if( $dropdown_array )
	{
		foreach ($dropdown_array as $group => $values) {
			$options .= '<optgroup label="' . ucwords( str_replace( '_', ' ', $group ) ) . '">';
			foreach ($values as $key => $value) {
				$selected = '';
				if( isset($logics['fcc_logic_type_selection'][$counter]) )
				{
					$selected = $logics['fcc_logic_type_selection'][$counter] == $key ? 'selected="selected"' : '';
				}
				$options .= '<option value="' . $key . '" '.$selected.'>' . $value . '</option>';
			}
			$options .= '</optgroup>';
		}
	}

	return '<select id="fcc_logic_type_selection_'.$counter.'" name="fcc_logic_type_selection[]">' .
			$options . 
			'</select>';
}

/**
 *
 */
function _build_operator_selection_dropdown_html( $logics, $counter = 0 ) 
{
	$selected1 = $selected2 = '';
	if( isset($logics['fcc_logic_operator_selection'][$counter]) )
	{
		$selected1 = $logics['fcc_logic_operator_selection'][$counter]=='equal' ? 'selected="selected"' : '';
		$selected2 = $logics['fcc_logic_operator_selection'][$counter]=='notequal' ? 'selected="selected"' : '';
	}
	return '<select id="fcc_logic_operator_selection_'.$counter.'" name="fcc_logic_operator_selection[]">' .
			'<option value="equal" '.$selected1.'>is equal to</option>' .
			'<option value="notequal" '.$selected2.'>is not equal to</option>' .
			'</select>';
}

/**
 *
 */
function _build_selection_selection_dropdown_html( $logics, $counter = 0 )
{

	$type_sel = isset($logics['fcc_logic_type_selection'][$counter]) && !empty($logics['fcc_logic_type_selection'][$counter])
					? $logics['fcc_logic_type_selection'][$counter] : 'category';

	$sel_sel_array = _build_selection_selection_dropdown_array( $type_sel );

	$options = '';

	if( $sel_sel_array )
	{
		foreach ($sel_sel_array as $key => $value) 
		{
			$selected = '';
			if( isset($logics['fcc_logic_value_selection'][$counter]) )
			{
				$selected = in_array($value['id'], $logics['fcc_logic_value_selection'][$counter]) ? 'selected="selected"' : '';

			}
			$options .= '<option value="'.$value['id'].'" '.$selected.'>'.$value['text'].'</option>';
		}
	}

	return '<select style="width:50%;" multiple="multiple" name="fcc_logic_value_selection['.$counter.'][]" id="fcc_logic_value_selection_'.$counter.'">'.$options.'</select>';
}

/* OPTIONS HTML */

/**
 *
 */
