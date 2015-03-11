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
	//**$logics = get_post_meta( $post->ID, '_footer_custom_code_logics', true );
	
	//$categories = get_tags();

	if( count( $fcc_logics['fcc_logic_type_selection'] ) > 0 )
	{
		echo '<pre>'.print_r($fcc_logics,true).'</pre>';
		$logic_rows = '';
		for ($i=0; $i < count( $fcc_logics['fcc_logic_type_selection'] ); $i++) { 
			if( isset($fcc_logics['ffc_logic_condition'][$i-1]) && $fcc_logics['ffc_logic_condition'][$i-1] == 'or' )
			{
				$logic_rows .= '<p> <input type="button" name="" id="" value="or" class="button" /> </p>';
			}
			$logic_rows .= '<p id="fcc_logic_row_'.$i.'">
								'._build_type_selection_dropdown_html( $post, $i ).'
								'._build_operator_selection_dropdown_html( $post, $i ).'
								<select style="width:50%;" multiple="multiple" name="fcc_logic_value_selection['.$i.'][]" id="fcc_logic_value_selection_'.$i.'"></select>
								<input type="button" name="fcc_logic_button_and" id="fcc_logic_button_and" class="button" value="and" />
							</p>';
		}

	}
	else
	{
		$logic_rows .= '<p>
						'._build_type_selection_dropdown_html( $post, 0 ).'
						'._build_operator_selection_dropdown_html( $post, 0 ).'
						<select style="width:50%;" multiple="multiple" name="fcc_logic_value_selection[0][]" id="fcc_logic_value_selection_0"></select>
						<input type="button" name="fcc_logic_button_and" id="fcc_logic_button_and" class="button" value="and" />
					</p>';
	}
	?>
	<div id="post-formats-select">
		<div id="ffc_logic_rows_div">
			<?php echo $logic_rows;?>
		</div>
	</div>
	<div id="post-formats-select">
		<label for="fcc_apply_only_if">
			<input type="checkbox" id="fcc_apply_only_if" name="fcc_apply_only_if" value="1" <?php echo $apply_only_if==1?'checked="checked"':''; ?> >
			 Apply Only If:
		</label>
		<p>
			<?php echo _build_type_selection_dropdown_html( $post, 0 ); ?>
			<?php echo _build_operator_selection_dropdown_html( $post, 0 ); ?>
			<select style="width:50%;" multiple="multiple" name="fcc_logic_value_selection[0][]" id="fcc_logic_value_selection_0"></select>
			<input type="button" name="fcc_logic_button_and" id="fcc_logic_button_and" class="button" value="and" />
		</p>
		<p>
			<input type="hidden" name="ffc_logic_condition[0]" id="ffc_logic_condition_0" value="and" />
			<?php echo _build_type_selection_dropdown_html( $post, 1 ); ?>
			<?php echo _build_operator_selection_dropdown_html( $post, 1 ); ?>
			<select style="width:50%;" multiple="multiple" name="fcc_logic_value_selection[1][]" id="fcc_logic_value_selection_1"></select>
			<input type="button" name="fcc_logic_button_and" id="fcc_logic_button_and" class="button" value="and" />
		</p>
		<p>
			<input type="hidden" name="ffc_logic_condition[1]" id="ffc_logic_condition_1" value="and" />
			<?php echo _build_type_selection_dropdown_html( $post, 2 ); ?>
			<?php echo _build_operator_selection_dropdown_html( $post, 2 ); ?>
			<select style="width:50%;" multiple="multiple" name="fcc_logic_value_selection[2][]" id="fcc_logic_value_selection_2"></select>
			<input type="button" name="fcc_logic_button_and" id="fcc_logic_button_and" class="button" value="and" />
		</p>
		<p> <input type="button" name="" id="" value="or" class="button" /> </p>
		<p>
			<input type="hidden" name="ffc_logic_condition[2]" id="ffc_logic_condition_2" value="or" />
			<?php echo _build_type_selection_dropdown_html( $post, 3 ); ?>
			<?php echo _build_operator_selection_dropdown_html( $post, 3 ); ?>
			<select style="width:50%;" multiple="multiple" name="fcc_logic_value_selection[3][]" id="fcc_logic_value_selection_3"></select>
			<input type="button" name="fcc_logic_button_and" id="fcc_logic_button_and" class="button" value="and" />
		</p>
		<p>
			<input type="hidden" name="ffc_logic_condition[3]" id="ffc_logic_condition_3" value="and" />
			<?php echo _build_type_selection_dropdown_html( $post, 4 ); ?>
			<?php echo _build_operator_selection_dropdown_html( $post, 4 ); ?>
			<select style="width:50%;" multiple="multiple" name="fcc_logic_value_selection[4][]" id="fcc_logic_value_selection_4"></select>
			<input type="button" name="fcc_logic_button_and" id="fcc_logic_button_and" class="button" value="and" />
		</p>
		<p> <input type="button" name="" id="" value="or" class="button" /> </p>
	</div>
	<?php
}

/**
 *
 */
function _build_type_selection_dropdown_html( $post, $counter = 0 ) 
{
	$dropdown_array = _build_type_selection_dropdown_array();

	$options = '';

	if( $dropdown_array )
	{
		foreach ($dropdown_array as $group => $values) {
			$options .= '<optgroup label="' . ucwords( str_replace( '_', ' ', $group ) ) . '">';
			foreach ($values as $key => $value) {
				$options .= '<option value="' . $key . '">' . $value . '</option>';
			}
			$options .= '</optgroup>';
		}
	}

	return '<select id="fcc_logic_type_selection_'.$counter.'" name="fcc_logic_type_selection['.$counter.']">' .
			$options . 
			'</select>';
}

/**
 *
 */
function _build_operator_selection_dropdown_html( $post, $counter = 0 ) 
{
	return '<select id="fcc_logic_operator_selection_'.$counter.'" name="fcc_logic_operator_selection['.$counter.']">' .
			'<option value="equal">is equal to</option>' .
			'<option value="notequal">is not equal to</option>' .
			'</select>';
}