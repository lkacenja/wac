<?php

function wac_pathauto($op) {
  switch ($op) {
    case 'settings':
      $settings = array();
      // Path auto assumes that an entity and the module that define it will have the same name.
      // Seems worse to have incorrectly named patterns based on entity than module.
      $settings['module'] = 'chart';
      $settings['token_type'] = 'chart';
      $settings['groupheader'] = t('Chart Paths');
      $settings['patterndescr'] = t('Default path pattern (applies to all content types with blank patterns below)');
      $settings['patterndefault'] = 'chart/[chart:title]';
      $settings['batch_update_callback'] = 'wac_update_alias_batch';
      $languages = array();
      if (module_exists('locale')) {
        $languages = array(LANGUAGE_NONE => t('language neutral')) + locale_language_list('name');
      }
      foreach (wac_get_chart_types() as $chart_type => $chart) {
        if (count($languages) && variable_get('language_content_type_' . $chart_type, 0)) {
          $settings['patternitems'][$chart_type] = t('Default path pattern for @chart_type (applies to all @chart_type content types with blank patterns below)', array('@chart_type' => $chart['title']));
          foreach ($languages as $lang_code => $lang_name) {
            $settings['patternitems'][$chart_type . '_' . $lang_code] = t('Pattern for all @language @chart_type paths', array('@chart_type' =>  $chart['title'], '@language' => $lang_name));
          }
        }
        else {
          $settings['patternitems'][$chart_type] = t('Pattern for all @chart_type paths', array('@chart_type' => $chart['title']));
        }
      }
      return (object) $settings;
    default:
      break;
  }
}

function wac_update_alias($chart, $op, array $options = array()) {
  $options += array(
    'language' => isset($chart->language) ? $chart->language : LANGUAGE_NONE,
  );
  // Skip processing if the chart has no pattern.
  if (!pathauto_pattern_load_by_entity('chart', $chart->type, $options['language'])) {
    return;
  }
  module_load_include('inc', 'pathauto');
  $uri = entity_uri('chart', $chart);
  pathauto_create_alias('chart', $op, $uri['path'], array('chart' => $chart), $chart->type, $options['language']);
}

function wac_update_alias_multiple(array $pids, $op, array $options = array()) {
  $options += array('message' => FALSE);

  $premises = entity_load('chart', $pids);
  foreach ($premises as $chart) {
    wac_update_alias($chart, $op, $options);
  }

  if (!empty($options['message'])) {
    drupal_set_message(format_plural(count($pids), 'Updated URL alias for 1 premise.', 'Updated URL aliases for @count premises.'));
  }
}

function wac_update_alias_batch() {
  $cids = array();
  $query = db_select('wac', 'w');
  $query->fields('w', array('cid'));
  $resource = $query->execute();
  while ($result = $resource->fetchObject()) {
    $cids[] = $result->cid;
  }
  wac_update_alias_multiple($cids, 'update');
}
