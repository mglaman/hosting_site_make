<?php

/**
 * @file
 * Provision/Drush hooks for the hosting_site_make module.
 *
 * These are the hooks that will be executed by the drush_invoke function.
 */

/**
 * Implementation of hook_drush_command().
 */
function provision_site_make_drush_command() {
  $items['provision-site_make'] = array(
    'description' => 'Builds the site.make file in the site directory.',
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  return $items;
}

/**
 * Implements drush_hook_COMMAND_pre_validate().
 */
function drush_provision_site_make_pre_validate() {
  /** Set offline mode to true and re-generate the settings.php. This will write
   * $conf['site_offline'] = 1; to the settings.php
   */
  drush_log(dt("Putting the site under maintenance"));
  d()->site_enabled = FALSE;
  _provision_drupal_create_settings_file();
  provision_drupal_push_site();
}

/**
 * Implements the provision-site_make command.
 */
function drush_provision_site_make() {
  drush_errors_on();
  if (d()->type === 'site') {
    $path = d()->site_path;
    $make_path = $path . '/site.make';

    // If the make doesn't exist, append .yml
    if (!file_exists($make_path)) {
      $make_path .= '.yml';
    }
    provision_backend_invoke(d()->name, 'make', array($make_path, $path), array(
      '--no-core',
      'contrib-destination' => '.',
      '--yes',
    ));
  }
}

/**
 * Implements drush_hook_post_COMMAND().
 */
function drush_provision_site_make_post_provision_site_make() {
  // Set site_offline to false and regenerate the config
  drush_log(dt("Bringing the site out of maintenance"));
  d()->site_enabled = TRUE;
  _provision_drupal_create_settings_file();
  provision_drupal_push_site();
}
