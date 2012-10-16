<?php

function sitenow_articles_create_menu() {
	// create menu item for sitenow_articles panel page
	menu_rebuild();
    $item = array(
    'link_path' => drupal_get_normal_path('articles'),
    'link_title' => 'Articles',
    'menu_name' => 'main-menu',
    );
  
    $mlid = menu_link_save($item);
    variable_set('sitenow_articles_mlid', $mlid);
    menu_cache_clear_all(); 
  }

function sitenow_articles_delete_menu() {
     // remove menu link
     menu_link_delete(variable_get('sitenow_articles_mlid'));
     menu_cache_clear_all(); 
     // remove variable
     variable_del('sitenow_articles_mlid');  
  }