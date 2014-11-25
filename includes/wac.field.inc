<?php


function wac_field_widget_info() {
 return array(
    'wac_text_from_file' => array(
      'label' => t('WAC Select From File'),
      'field types' => array('text'),
      'settings' => array('size' => 1),
      'behaviors' => array(
        'multiple values' => FIELD_BEHAVIOR_DEFAULT,
        'default value' => FIELD_BEHAVIOR_DEFAULT,
      ),
      'weight' => 1
    )
  );
}

function wac_field_widget_settings_form($field, $instance) {
  $form = array();
  if ($instance['widget']['type'] == 'wac_text_from_file') {
    $all_fields = field_info_instances($instance['entity_type'], $instance['bundle']);
    $file_fields = array_filter($all_fields, 'wac_field_is_file_field'); 
    if (!empty($file_fields)) {
      $options = array('' => '- Select -');
      foreach($file_fields AS $key => $field) {
        $options[$key] = $field['label'] . ' (' . $key . ')';
      }
      $form['wac_text_from_file_file_field'] = array(
        '#type' => 'select',
        '#title' => t('Select a File Field'),
        '#description' => t('Web Accessible Charts will attempt to read the header of files uploaded with this field to use as axes on charts.'),
        '#options' => $options,
        '#default_value' => !empty($instance['widget']['settings']['wac_text_from_file_file_field']) ? $instance['widget']['settings']['wac_text_from_file_file_field'] : ''
      );
    }
    else {
      $form['wac_text_from_file_file_field'] = array(
        '#type' => 'item',
        '#title' => t('Select a File Field'),
        '#markup' => t('No usable file fields were found. WAC Select From File fields require a core generic file field (not image) to function.'),
      );
    }
  }
  return $form;
}

function wac_field_is_file_field($field_info) {
  return $field_info['widget']['type'] == 'file_generic' ? TRUE : FALSE;
}

function wac_field_is_wac_text_from_file($field_info) {
  return $field_info['widget']['type'] == 'wac_text_from_file' ? TRUE : FALSE;
}

function wac_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {
  if ($instance['widget']['type'] == 'wac_text_from_file') {
    $options = array();
    if (!empty($instance['widget']['settings']['wac_text_from_file_file_field'])) {
      $file_field_name = $instance['widget']['settings']['wac_text_from_file_file_field'];
      if (!empty($form['#entity']->{$file_field_name})) {
        $file_field = $form['#entity']->{$file_field_name};
        if (!empty($file_field[$langcode][0])) {
          $file = (object) $file_field[$langcode][0];
          $options = wac_get_data_keys_from_file($file);
        }
      }
    }
    $widget = $element + array(
      '#type' => 'select',
      '#options' => $options,
      '#default_value' => isset($items[$delta]['value']) ? $items[$delta]['value'] : NULL,
      '#size' => $instance['widget']['settings']['size'],
      '#maxlength' => $field['settings']['max_length'],
      '#attributes' => array('class' => array('wac-text-as-file')),
      '#disabled' => empty($options) ? TRUE : FALSE,
      '#multiple' => FALSE
    );
    $element['value'] = $widget;
  }
  return $element;
}
