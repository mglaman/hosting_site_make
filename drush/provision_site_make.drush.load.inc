<?php

/**
 * Implements hook_drush_load().
 *
 * In a drush contrib check if the frontend part (hosting_hook variant) is enabled.
 */
function provision_site_make_drush_load() {
  $features = drush_get_option('hosting_features', array());
  $hook_feature_name = 'site_make';

  return array_key_exists($hook_feature_name, $features) // Front-end module is installed...
    && $features[$hook_feature_name];                    // ... and enabled.
}

