<?php

/**
 * Get the pid prefix based on URL alias
 */
function _get_pid_prefix($path){
    $file_path = module_load_include('inc', 'content', 'includes/path');
    if ($file_path === FALSE) {
        return NULL;
    }
    $pid = drupal_lookup_path('source', $path, 'en');
    $pid_arr = explode("/", $pid);
    $pid_arr_length = count($pid_arr);
    $pid = $pid_arr[$pid_arr_length-1];
    $pid_arr = explode(":", $pid);
    return $pid_arr[0];
}
