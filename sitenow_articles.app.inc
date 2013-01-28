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
  // Provide alternative help text due to using migrate instead of default content
  $form['demo_content_group']['demo_content_current']['#markup'] = "Enabling the demo content will add content to the site that can help to understand how the app functions. You may then edit or delete that content after this has been enabled.<br /><br/>";

  // If the SiteNowArticles migration has run and the sitenow_articles_content
  // module is currently disabled, keep it that way.
  if(migration_log('SiteNowArticles') && !module_exists('sitenow_articles_content')) {
    $form['demo_content_group']['demo_content_button']['#suffix'] = "Demo content has already been enabled for this site, the content is already available.";
    $form['demo_content_group']['demo_content_button']['#disabled'] = TRUE;
  }
}
