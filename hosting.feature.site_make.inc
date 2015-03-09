<?php
/**
 * @file
 *   Expose the extra tasks feature to hostmaster.
 */

/**
 * Implements hook_hosting_feature().
 */
function hosting_site_make_hosting_feature() {
  $features['site_make'] = array(
    'title' => t('Site make'),
    'description' => t("Allows a site to have its modules built from a makefile in the sites directory."),
    'status' => HOSTING_FEATURE_ENABLED,
    // 'status' => HOSTING_FEATURE_DISABLED,
    'module' => 'hosting_site_make',
  );
  return $features;
}
