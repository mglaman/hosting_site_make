<?php

/**
 * @file
 * Drush include for site make
 */

function drush_hosting_site_make_pre_hosting_task($task) {
  $task =& drush_get_context('HOSTING_TASK');
  if ($task->ref->type === 'site' && $task->task_type === 'site_make') {
    // Load the site
    $site = node_load($task->rid);
    $platform = node_load($site->platform);

    $make_path = $platform->{'publish_path'} . '/sites/' . $site->title . '/site.make';
    $make_path_yml = $make_path . '.yml';

    if (file_exists($make_path) || file_exists($make_path_yml)) {
      $task->site_make_path = $make_path;
    }
    else {
      drush_set_error("HOSTING_SITE_MAKE_NO_MAKE", dt("There isn't a valid site.make file in the site's directory."));
    }
  }
}
