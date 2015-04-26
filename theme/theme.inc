<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * the hook to modify display of islandora bookreader
 * 
 * @param array $variables
 */
function islandora_embed_process_islandora_internet_archive_bookreader(&$variables) {

    $parameters = drupal_get_query_parameters();
    if(isset($parameters['ui']) && $parameters['ui'] == 'embed'){
        $bookreader_embed_settings = array();
        if(isset($parameters['height']) && $parameters['height'] != ''){
            $bookreader_embed_settings['height'] = $parameters['height'];
        }
        if(isset($parameters['width']) && $parameters['width'] != ''){
            $bookreader_embed_settings['width'] = $parameters['width'];
        }
        if(count($bookreader_embed_settings) > 0){
          drupal_add_js(array('islandora_bookreader_embed' => $bookreader_embed_settings), 'setting');
        }
        drupal_add_js(drupal_get_path('module', 'islandora_embed') . '/js/embed.js', array('group' => JS_LIBRARY));
    }
}