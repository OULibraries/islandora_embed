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
        $bookreader_embed_settings = array();
        if(isset($parameters['height']) && $parameters['height'] != '') {
            $bookreader_embed_settings['height'] = $parameters['height'];
        }
        if(isset($parameters['width']) && $parameters['width'] != '') {
            $bookreader_embed_settings['width'] = $parameters['width'];
        }
        if(count($bookreader_embed_settings) > 0) {
            drupal_add_js(array('islandora_bookreader_embed' => $bookreader_embed_settings), 'setting');
        }
        drupal_add_js(drupal_get_path('module', 'islandora_embed') . '/js/embed.js', array('group' => JS_LIBRARY));
    }
}

/**
 * Hide the display of the side bars
 * 
 * @param array $variables: page html setup
 */
function islandora_embed_preprocess_html(&$variables)
{
    if(!empty($variables["directory"]) && $variables["directory"] == "sites/all/themes/entity_iframe_theme"){
        $variables["classes_array"][3] = "no-sidebars";
        $variables["page"]["page_top"]["toolbar"] = TRUE;
        $variables['classes_array'][] = "";
        $variables['title_attributes_array'][] = "";
        $variables['attributes_array'][] = "";
        $variables['content_attributes_array'] = "";
    }
    else{
        $variables['classes_array'][] = "";
        $variables['title_attributes_array'][] = "";
        $variables['attributes_array'][] = "";
        $variables['content_attributes_array'] = "";
    }
}
