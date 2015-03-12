<?php
/**
 * 
 */
function enqueue_scripts() 
{
	global $pagenow;

	$post = filter_input(INPUT_GET, 'post');

	if ('post.php' == $pagenow || 'post-new.php' == $pagenow )
	{
		$post_type = 'post-new.php' == $pagenow ? filter_input(INPUT_GET, 'post_type') : get_post_type($post);

		if ( 'footer_custom_code' == $post_type )
		{
			$url = plugin_dir_url( dirname(__FILE__) ) . 'assets/';
			wp_enqueue_style( 'select2-min-css', $url . 'css/select2.min.css' );
			/*wp_enqueue_style( 'codemirror-css', $url . 'css/codemirror.css' );
			wp_enqueue_script( 'codemirror-js', $url . 'js/codemirror.js', array(), '1.0.0', true );
			wp_enqueue_script( 'codemirror-javascript-js', $url . 'js/javascript.js', array(), '1.0.0', true );
			wp_enqueue_script( 'codemirror-css-js', $url . 'js/css.js', array(), '1.0.0', true );
			wp_enqueue_script( 'codemirror-php-js', $url . 'js/php.js', array(), '1.0.0', true );*/
			wp_enqueue_script( 'suggest' );
			wp_enqueue_script( 'select2-min-js', $url . 'js/select2.min.js', array(), '2.0.*', true );
			wp_enqueue_script( 'plugin-js', $url . 'js/custom.js', array('jquery'), '1.0.0', true );
		}
	}
}

/**
 *
 */
function register_custom_post_type() 
{
	register_post_type(
		'footer_custom_code',
		[
			'label' => __('Footer Codes'),
			'labels' => [
				'name' => __('Footer Custom Codes'),
				'singular_name' => __('Footer Custom Code'),
				'menu_name' => __('Footer Codes'),
				'menu_admin_bar' => __('Add New Custom Code'),
				'all_items' => __('All Footer Codes'),
				'add_new' => __('Add New Footer Custom Code'),
				'add_new_item' => __('Add New Code'),
				'edit_item' => __('Edit Footer Custom Code'),
				'new_item' => __('New Footer Custom Code'),
				'view_item' => __('View Footer Custom Code'),
				'not_found' => __('No Footer Custom Code has been added yet!'),
				'not_found_in_trash' => __('No Footer Custom Code has been added yet!')
			],
			'description' => __('Add custom CSS, Javascript, PHP codes if footer of any page or post.'),
			'hierarchical' => false,
			'public' => true,
			'exclude_from_search' => true,
			'publicly_queryable' => false,
			'supports' => ['title'],
			'can_export' => true,
			'rewrite' => false,
			'query_var' => false,
			'register_meta_box_cb' => 'footer_custom_code_metaboxes'
		]
	);

	register_taxonomy( 'custom_taxonomy', 'post', ['label' => 'Custom Taxonomy', 'hierarchical' => true] );
}

/**
 *
 */
function footer_custom_code_metaboxes( $post )
{
	wp_nonce_field( 'custom_footer_code_nonce_submit', 'custom_footer_code_nonce', true, true );

	add_meta_box ( 'footer_custom_code_content', __('Custom Code'), 'custom_code_metabox_content_html', 'footer_custom_code', 'advanced', 'core' );

	add_meta_box ( 'footer_custom_code_type', __('Custom Code Type'), 'custom_code_metabox_types_html', 'footer_custom_code', 'side' );

	add_meta_box ( 'footer_custom_code_placement', __('Custom Code Placement'), 'custom_code_metabox_placement_html', 'footer_custom_code', 'side' );

	add_meta_box ( 'footer_custom_code_logic', __('Custom Code Logic'), 'custom_code_metabox_logic_html', 'footer_custom_code', 'advanced' );
}

/**
 *
 */
function custom_footer_edit_code_columns( $columns ) 
{
	$columns = [
		'cb' => '<input type="checkbox" />',
		'title' => __('Title'),
		'fcc_type' => __('Type'),
		'fcc_placement' => __('Placement'),
		'fcc_priority' => __('Priority'),
		'date' => __( 'Date' )
	];

	return $columns;
}

/**
 *
 */
function manage_footer_custom_code_columns( $column, $post_id ) 
{
	switch ( $column ) {
		case 'fcc_type':
			$type = get_post_meta( $post_id, '_footer_custom_code_type', true );
			switch ($type) {
				case 'css': echo 'CSS'; break;
				case 'js': echo 'Javascaript'; break;
				case 'php': echo 'PHP'; break;
			}
			break;
		case 'fcc_placement':
			$placement = get_post_meta( $post_id, '_footer_custom_code_placement', true );
			switch ($placement) {
				case 'inline': echo 'Inline Script'; break;
				case 'external': echo 'External File'; break;
			}
			break;
		case 'fcc_priority':
			echo get_post_meta( $post_id, '_footer_custom_code_priority', true );
			break;
		
		default:
			# code...
			break;
	}

}

/**
 *
 */
function custom_footer_code_save_fields_data( $post_id ) 
{
	$screen = get_current_screen();

	if( 'footer_custom_code' == $screen->post_type )
	{
		$input_post = filter_input_array(INPUT_POST);

		/*if ( !_custom_foooter_code_basic_validation( $post_id ) || !_custom_foooter_code_field_validation( $post_id ) ) {
            return $post_id;
        }*/
		if( $input_post ) 
		{
			// echo '<pre>'.print_r($input_post, true).'</pre>';exit;
			$type = sanitize_text_field( $input_post['footer_custom_code_type'] );
			$placement = sanitize_text_field( $input_post['footer_custom_code_placement'] );
			$priority = sanitize_text_field( $input_post['footer_custom_code_priority'] );
			$content = sanitize_text_field( $input_post['footer_custom_code_content'] );
			$apply_only_if = sanitize_text_field( $input_post['fcc_apply_only_if'] );

			$logics = array();
			if( $apply_only_if == 1 )
			{
				$logics = array( 
							'fcc_logic_type_selection' => $input_post['fcc_logic_type_selection'], 
							'fcc_logic_operator_selection' => $input_post['fcc_logic_operator_selection'], 
							'fcc_logic_value_selection' => $input_post['fcc_logic_value_selection'], 
							'ffc_logic_condition' => $input_post['ffc_logic_condition']
						);
			}

			update_post_meta( $post_id, '_footer_custom_code_type', $type );
			update_post_meta( $post_id, '_footer_custom_code_placement', $placement );
			update_post_meta( $post_id, '_footer_custom_code_priority', $priority );
			update_post_meta( $post_id, '_footer_custom_code_content', $content );
			update_post_meta( $post_id, '_fcc_apply_only_if', $apply_only_if );
			update_post_meta( $post_id, '_footer_custom_code_logics', serialize( $logics ) );
		}
	} 



}

/*function _custom_foooter_code_basic_validation( $post_id ) {
	// Check if our nonce is set.
    if ( ! isset( $_POST['metaboxnonce'] ) ) {
        return false;
    }
    // Verify that the nonce is valid.
    if ( ! wp_verify_nonce( $_POST['metaboxnonce'], 'metaboxnonce' ) ) {
        return false;
    }
    // If this is an autosave, our form has not been submitted, so we don't want to do anything.
    if ( defined( 'DOING_AUTOSAVE' ) && DOING_AUTOSAVE ) {
        return false;
    }
    // Check the user's permissions.
    if ( isset( $_POST['post_type'] ) && 'footer_custom_code' == $_POST['post_type'] ) {
        if ( ! current_user_can( 'edit_page', $post_id ) ) {
            return false;
        }
    } else {
        if ( ! current_user_can( 'edit_post', $post_id ) ) {
            return false;
        }
    }

    return true;
}

function _custom_foooter_code_field_validation( $post_id ) {
	return false;
}*/



/**
 *
 */

function footer_custom_code_help() 
{
	$screen = get_current_screen();

	if( 'footer_custom_code' == $screen->post_type )
	{
		$screen->add_help_tab([
			'id' => 'footer_custom_code_help',
			'title' => 'Custom Footer Code Help',
			'content' => '<h3>Help Title</h3><p>Help content</p>'
		]);
		echo '<style>#edit-slug-box,#screen-options-link-wrap,#normal-sortables{display:none;}</style>';
	} 
}

/**
 *
 */
function run_footer_custom_code() 
{
	$codes_query = new WP_Query([
		'post_type' => 'footer_custom_code',
		'post_status' => 'publish',
		'posts_per_page' => -1
	]);

	$footer_codes = array();
	if( $codes_query->have_posts() ) 
	{
		while ( $codes_query->have_posts() ) 
		{
			$codes_query->the_post();

			$type = get_post_meta( get_the_ID(), '_footer_custom_code_type', true );
			$content = get_post_meta( get_the_ID(), '_footer_custom_code_content', true );
			$placement = get_post_meta( get_the_ID(), '_footer_custom_code_placement', true );
			$priority = get_post_meta( get_the_ID(), '_footer_custom_code_priority', true );

			$footer_codes[$priority] = [
				'type' => $type,
				'placement' => $placement,
				'content' => $content
			];
		}
	}

	if( count( $footer_codes ) > 0 )
	{
		ksort( $footer_codes );
		foreach ($footer_codes as $periority => $data) {
			if( empty( $data['content'] ) )
			{
				continue; // Don't want to show empty tags.
			}

			switch ($data['type']) {
				case 'js':
					echo '
					<script type="text/javascript">' . strip_tags( $data['content'] ) . '</script>';
					break;
				case 'css':
					echo '
					<style type="text/css">' . strip_tags( $data['content'] ) . '</style>';
					break;
				case 'php':
					eval ( strip_tags( $data['content'] ) ) ;
					break;
			}
		}
	}
}

/**
 *
 */
function _build_type_selection_dropdown_array() 
{
	$dropdown_array = array();
	
	$builtin_taxonomies = (array) get_taxonomies( ['_builtin' => 'true', 'object_type' => ['post']]);
	$nonbuiltin_taxonomies = (array) get_taxonomies(['_builtin' => 'false', 'object_type' => ['post']]);

	$taxonomies = array_merge($builtin_taxonomies, $nonbuiltin_taxonomies);

	if( $taxonomies )
	{
		foreach ($taxonomies as $taxonomy) {
			$dropdown_array['taxonomies'][$taxonomy] = ucwords( str_replace( '_', ' ', $taxonomy ) );
		}
	}

	$post_types = get_post_types(['_builtin' => true]);

	if( $post_types )
	{
		foreach ($post_types as $post_type) {
			if( $post_type != 'footer_custom_code' ) {
				$dropdown_array['post_types'][$post_type] = ucwords( str_replace( '_', ' ', $post_type ) );
			}
		}
	}

	$dropdown_array['plugins']['wpml'] = 'WPML';

	
	$dropdown_array['modules']['active_theme'] = 'Active Theme';
	$dropdown_array['modules']['active_plugin'] = 'Active Plugin';


	return $dropdown_array;
}

/**
 *
 */
function _build_selection_selection_dropdown_array( $fcc_type ) 
{
	$opt_array = array();
	if( !isset($fcc_type) || empty($fcc_type) )
	{
		return $opt_array;
	}

	/*switch ( $fcc_type ) 
	{
		case 'category':
			$options_array = get_categories();
			break;
		case 'post_tag':
			$options_array = get_tags();
			break;
		default:
			$options_array = array();
			break;
	}*/

	$options_array = get_terms( 'link_category' );

	if( count( $options_array ) > 0 )
	{
		foreach ($options_array as $key => $category) {
			$opt_array[$key]['id'] = $category->term_id;
			$opt_array[$key]['text'] = $category->name;
		}
	}

	return $opt_array;
}