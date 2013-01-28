<?php
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

/*
 * Implements hook_form_FORM_ID_alter().
 */
function sitenow_articles_form_apps_demo_content_form_alter(&$form, &$form_state, $form_id) {
  $app = $form['app']['#value']['machine_name'];
  if ($app === 'sitenow_articles') {
    // If the SiteNowArticles migration has run and the sitenow_articles_content
    // module is currently disabled, keep it that way.
    if(migration_log('SiteNowArticles') && !module_exists('sitenow_articles_content')) {
      $form['demo_content_group']['demo_content_button']['#suffix'] = "Demo content has already been enabled for this site, the content is already available.";
      $form['demo_content_group']['demo_content_button']['#disabled'] = TRUE;
    }
  }
}
