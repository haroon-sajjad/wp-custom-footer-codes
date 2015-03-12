<?php
/**
 * @package Hello_Dolly
 * @version 1.7
 */
/*
Plugin Name: Footer Custom Code
Plugin URI: http://test.com/
Description: Add custom CSS, Javascript, PHP codes if footer of any page or post.
Version: 1.7
License: GPLv2 or later
*/

require_once('includes/functions.inc');
require_once('includes/htmls.inc');

add_action('admin_init', 'enqueue_scripts');

add_action('init', 'register_custom_post_type');

add_action('save_post', 'custom_footer_code_save_fields_data');

//add_action('edit_form_advanced', 'footer_custom_code_textarea');

add_filter('manage_edit-footer_custom_code_columns', 'custom_footer_edit_code_columns');

add_action( 'manage_footer_custom_code_posts_custom_column', 'manage_footer_custom_code_columns', 10, 2 );

add_action('admin_head', 'footer_custom_code_help');

add_action('wp_footer', 'run_footer_custom_code', 1000);

add_action( 'wp_ajax_fcc_logic_action', function()
{
	$fcc_type = filter_input(INPUT_POST, 'fcc_type');

	$cat_json = _build_selection_selection_dropdown_array( $fcc_type );

	echo json_encode( $cat_json );

	wp_die();
} );