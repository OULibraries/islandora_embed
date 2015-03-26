<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

function islandora_embed_preprocess_islandora_embed(array &$variables){
    drupal_add_css("$module_path/css/book_page_download.css");
}