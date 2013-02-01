<?php

/**
 * @file
 * Migration code for SiteNow Articles content.
 */

/**
 * Implements hook_migrate_api().
 */
function sitenow_articles_content_migrate_api() {
  $api = array(
    'api' => 2,
    'migrations' => array(
      'SiteNowArticles' => array('class_name' => 'SiteNowArticlesMigration'),
    ),
  );
  return $api;
}

// Initial SiteNowArticlesMigration class.
// @TODO: Refactor to abstract common parts into a "SiteNowMigration" class that
// could then be extended by each app.
class SiteNowArticlesMigration extends Migration {

  public function __construct() {
    parent::__construct(MigrateGroup::getInstance('SiteNow'));

    // Avoid known line ending issue: drupal.org/node/1705850
    ini_set('auto_detect_line_endings', TRUE);

    $this->description = t('Import SiteNow Article nodes.');

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'nid' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
        ),
      ),
      MigrateDestinationNode::getKeySchema()
    );

    // Create a MigrateSource object.
    $this->source = new MigrateSourceCSV(drupal_get_path('module', 'sitenow_articles_content') . '/import/articles.csv', $this->csvcolumns(), array('header_rows' => 1));

    $this->destination = new MigrateDestinationNode('article');

    // Bring on the field mappings
    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('body', 'body');

    // Copy an image file, write DB record to files table, and save in Field storage.
    // We map the filename (relative to the source_dir below) to the field itself.
    $this->addFieldMapping('field_image', 'image');
    // Here we specify the directory containing the source files.
    $this->addFieldMapping('field_image:source_dir')
         ->defaultValue(drupal_get_path('module', 'sitenow_articles_content') . "/import");
    // And we map the alt and title values in the database to those on the image.
    $this->addFieldMapping('field_image:alt', 'image_alt');
    $this->addFieldMapping('field_image:title', 'image_title');

    // Author mapping. Defaults to user 1.
    $this->addFieldMapping('uid', 'uid')->defaultValue(1);
    $this->addFieldMapping('is_new', 'is_new')->defaultValue(TRUE);
    $this->addFieldMapping('promote', 'promote')->defaultValue(FALSE);
  }

  // Function for the CSV document
  function csvcolumns() {
    // Title", "Path", "Body"
    $columns[0] = array('nid', 'nid');
    $columns[1] = array('title', 'Title');
    $columns[2] = array('body', 'Body');
    $columns[3] = array('image', 'Image');
    $columns[4] = array('image_alt', 'Image Alt');
    $columns[5] = array('image_title', 'Image title');
    $columns[6] = array('promote', 'Promote');
    return $columns;
  }
}
