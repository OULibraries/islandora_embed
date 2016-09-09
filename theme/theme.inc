<?php
/**
 * the hook to modify display of islandora bookreader
 *
 * @param array $variables
 */
function islandora_embed_process_islandora_internet_archive_bookreader(&$variables) 
{

    $parameters = drupal_get_query_parameters();
    if(isset($parameters['ui']) && $parameters['ui'] == 'embed') {
	drupal_add_http_header('X-Frame-Options', '');
    }
}
