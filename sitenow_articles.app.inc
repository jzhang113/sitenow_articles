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

/**
 * Implements hook_apps_app_configure_form().
 */
function sitenow_articles_apps_app_configure_form($form, &$form_state) {
  global $base_url;

  if (module_exists('views')) {
    $view = views_get_view('articles');
    $feeds = array();

    // Any view display that defines a path at '/feeds/*' will be added.
    foreach ($view->display as $display) {
      if (stristr($display->display_options['path'], 'feeds')) {
        $feeds[] = l($base_url . '/' . $display->display_options['path'], $display->display_options['path']);
      }
    }

    $form = array(
      'feeds' => array(
        'title' => array(
          '#prefix' => '<h2>',
          '#suffix' => '</h2>',
          '#markup' => t('Feeds'),
        ),
        'description' => array(
          '#prefix' => '<p>',
          '#suffix' => '</p>',
          '#markup' => t('The following feeds are available to be consumed by external applications.'),
        ),
        'list' => array(
          '#theme' => 'item_list',
          '#items' => $feeds,
        ),
        'description' => array(
          '#prefix' => '<p>',
          '#suffix' => '</p>',
          '#markup' => t('These feeds are unfiltered and will display all articles sorted by most recent post date. The feed icons on each pane will use the filters applied to the pane.'),
        ),
      ),
    );
  }

  return $form;
}
