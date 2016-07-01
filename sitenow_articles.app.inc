<?php
/**
 * @file
 * App configuration.
 */

/**
 * Implements hook_apps_app_info().
 */
function sitenow_articles_apps_app_info() {
  return array(
    'configure form' => 'sitenow_articles_apps_app_configure_form',
    'demo content module' => 'sitenow_articles_content',
  );
}

function sitenow_articles_apps_app_configure_form($form, &$form_state) {
  // flush cache to assure all config got instantiated properly

  $form = array();
  return $form;
}
