<?php
/**
 * @file
 * sitenow_articles.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sitenow_articles_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function sitenow_articles_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function sitenow_articles_image_default_styles() {
  $styles = array();

  // Exported image style: articles_grid.
  $styles['articles_grid'] = array(
    'label' => 'Articles Grid',
    'effects' => array(
      13 => array(
        'name' => 'manualcrop_reuse',
        'data' => array(
          'reuse_crop_style' => 'crop_selection_rectangle_3-2',
        ),
        'weight' => 0,
      ),
      15 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 500,
          'height' => 333,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: articles_teaser.
  $styles['articles_teaser'] = array(
    'label' => 'Articles Teaser',
    'effects' => array(
      16 => array(
        'name' => 'manualcrop_reuse',
        'data' => array(
          'reuse_crop_style' => 'crop_selection_rectangle_3-2',
        ),
        'weight' => 0,
      ),
      18 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 500,
          'height' => 333,
        ),
        'weight' => 2,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function sitenow_articles_node_info() {
  $items = array(
    'article' => array(
      'name' => t('Article'),
      'base' => 'node_content',
      'description' => t('Use <em>articles</em> for time-sensitive content like news, press releases or blog posts.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
