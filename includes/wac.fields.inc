<?php

function wac_chart_fields() {
  $fields = array();
  // Common Fields Attached Below
  $description = array(
    'field_name' => 'alternate_description',
    'type' => 'text_long',
    'settings' => array(
      'rows' => 5
    ),
  );
  $description_instance = array(
    'field_name' => 'alternate_description',
    'entity_type' => 'chart',
    'bundle' => '',
    'label' => t('Alternate Description'),
    'description' => t('Description to use for alternate chart text. Should include semantic information about the chart as well as descriptive text.'),
    'required' => TRUE,
    'widget' => array(
      'type' => 'text_textarea',
      'weight' => 3,
    ),
    'display' => array(),
  );
  $data_file = array(
    'field_name' => 'data_file',
    'type' => 'file',
  );
  $data_file_instance = array(
    'field_name' => 'data_file',
    'entity_type' => 'chart',
    'bundle' => '',
    'label' => t('Data File'),
    'description' => t('Data file to use with this chart.'),
    'required' => TRUE,
    'settings' => array(
      'file_extensions' => 'csv tsv json',
      'file_directory' => 'chart_files',
    ),
    'widget' => array( 
      'type' => 'file_generic',
      'weight' => 4,
    ),
    'display' => array(),
  );
  $format_field = array(
    'field_name' => 'value_format',
    'type' => 'list_text',
    'settings' => array(
      'allowed_values' => wac_get_formats()
    ),
  );
  $format_instance = array(
    'field_name' => 'value_format',
    'entity_type' => 'chart',
    'bundle' => '',
    'label' => t('Value Format'),
    'description' => t('The format data values should use for display.'),
    'required' => TRUE,
    'widget' => array(
      'type' => 'options_select',
      'weight' => 4.5,
    ),
    'display' => array(),
  );
  $data_field = array(
    'field_name' => 'data_field',
    'type' => 'text',
  );
  $data_field_instance = array(
    'field_name' => 'data_field',
    'entity_type' => 'chart',
    'bundle' => '',
    'label' => t('Alternate Data Field'),
    'description' => t('Field used for storing alternate data for each row.'),
    'required' => TRUE,
    'widget' => array(
      'type' => 'text_textfield',
      'weight' => 7,
    ),
    'display' => array(),
  );
  // Bar charts
  $fields['bar'] = array();
  $fields['bar']['alternate_description'] = array();
  $fields['bar']['alternate_description']['field'] = $description;
  $fields['bar']['alternate_description']['instance'] = array_merge($description_instance, array('bundle' => 'bar'));
  $fields['bar']['value_format'] = array();
  $fields['bar']['value_format']['field'] = $format_field;
  $fields['bar']['value_format']['instance'] = array_merge($format_instance, array('bundle' => 'bar'));
  $fields['bar']['data_file'] = array();
  $fields['bar']['data_file']['field'] = $data_file;
  $fields['bar']['data_file']['instance'] = array_merge($data_file_instance, array('bundle' => 'bar'));
  $fields['bar']['data_field'] = array();
  $fields['bar']['data_field']['field'] = $data_field;
  $fields['bar']['data_field']['instance'] = array_merge($data_field_instance, array('bundle' => 'bar'));
  $fields['bar']['x_axis']['field'] = array(
    'field_name' => 'x_axis',
    'type' => 'text',
  );
  $fields['bar']['x_axis']['instance'] = array(
    'field_name' => 'x_axis',
    'entity_type' => 'chart',
    'bundle' => 'bar',
    'label' => t('X Axis Field'),
    'description' => t('Field used for X Axis values.'),
    'required' => TRUE,
    'widget' => array(
      'type' => 'text_textfield',
      'weight' => 5,
    ),
    'display' => array(),
  );
  $fields['bar']['y_axis']['field'] = array(
    'field_name' => 'y_axis',
    'type' => 'text',
  );
  $fields['bar']['y_axis']['instance'] = array(
    'field_name' => 'y_axis',
    'entity_type' => 'chart',
    'bundle' => 'bar',
    'label' => t('Y Axis Field'),
    'description' => t('Field used for Y Axis values.'),
    'required' => TRUE,
    'widget' => array(
      'type' => 'text_textfield',
      'weight' => 6,
    ),
    'display' => array(),
  );
  // Pie
  $fields['pie'] = array();
  $fields['pie']['alternate_description'] = array();
  $fields['pie']['alternate_description']['field'] = $description;
  $fields['pie']['alternate_description']['instance'] = array_merge($description_instance, array('bundle' => 'pie'));
  $fields['pie']['value_format'] = array();
  $fields['pie']['value_format']['field'] = $format_field;
  $fields['pie']['value_format']['instance'] = array_merge($format_instance, array('bundle' => 'pie'));
  $fields['pie']['data_file'] = array();
  $fields['pie']['data_file']['field'] = $data_file;
  $fields['pie']['data_file']['instance'] = array_merge($data_file_instance, array('bundle' => 'pie'));
  $fields['pie']['data_field'] = array();
  $fields['pie']['data_field']['field'] = $data_field;
  $fields['pie']['data_field']['instance'] = array_merge($data_field_instance, array('bundle' => 'pie'));
  $fields['pie']['value']['field'] = array(
    'field_name' => 'value',
    'type' => 'text',
  );
  $fields['pie']['value']['instance'] = array(
    'field_name' => 'value',
    'entity_type' => 'chart',
    'bundle' => 'pie',
    'label' => t('Value Field'),
    'description' => t('Field to use as value in chart.'),
    'required' => TRUE,
    'widget' => array(
      'type' => 'text_textfield',
      'weight' => 5,
    ),
    'display' => array(),
  );
  $fields['pie']['pie_label']['field'] = array(
    'field_name' => 'pie_label',
    'type' => 'text',
  );
  $fields['pie']['pie_label']['instance'] = array(
    'field_name' => 'pie_label',
    'entity_type' => 'chart',
    'bundle' => 'pie',
    'label' => t('Label Field'),
    'description' => t('Field used for chart label.'),
    'required' => TRUE,
    'widget' => array(
      'type' => 'text_textfield',
      'weight' => 6,
    ),
    'display' => array(),
  );
  // Line Charts
  $fields['line'] = array();
  $fields['line']['alternate_description'] = array();
  $fields['line']['alternate_description']['field'] = $description;
  $fields['line']['alternate_description']['instance'] = array_merge($description_instance, array('bundle' => 'line'));
  $fields['line']['value_format'] = array();
  $fields['line']['value_format']['field'] = $format_field;
  $fields['line']['value_format']['instance'] = array_merge($format_instance, array('bundle' => 'line'));
  $fields['line']['data_file'] = array();
  $fields['line']['data_file']['field'] = $data_file;
  $fields['line']['data_file']['instance'] = array_merge($data_file_instance, array('bundle' => 'line'));
  $fields['line']['data_field'] = array();
  $fields['line']['data_field']['field'] = $data_field;
  $fields['line']['data_field']['instance'] = array_merge($data_field_instance, array('bundle' => 'line'));
  $fields['line']['x_axis']['field'] = array(
    'field_name' => 'x_axis',
    'type' => 'text',
  );
  $fields['line']['x_axis']['instance'] = array(
    'field_name' => 'x_axis',
    'entity_type' => 'chart',
    'bundle' => 'line',
    'label' => t('X Axis Field'),
    'description' => t('Field used for X Axis values.'),
    'required' => TRUE,
    'widget' => array(
      'type' => 'text_textfield',
      'weight' => 5,
    ),
    'display' => array(),
  );
  $fields['line']['y_axis']['field'] = array(
    'field_name' => 'y_axis',
    'type' => 'text',
  );
  $fields['line']['y_axis']['instance'] = array(
    'field_name' => 'y_axis',
    'entity_type' => 'chart',
    'bundle' => 'line',
    'label' => t('Y Axis Field'),
    'description' => t('Field used for Y Axis values.'),
    'required' => TRUE,
    'widget' => array(
      'type' => 'text_textfield',
      'weight' => 6,
    ),
    'display' => array(),
  );
  return $fields;
}


function wac_fields_from_data() {
  return array(
    'x_axis',
    'y_axis',
    'data_field',
    'percent',
    'pie_label'
  );
}
