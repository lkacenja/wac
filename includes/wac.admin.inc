<?php

function wac_chart_type_admin_form() {

  return array();
}

function wac_chart_add($form, $form_state, $chart) {
  if (empty($chart->cid)) {
    drupal_set_title(t('Create !type', array('!type' => $chart->title)));
    $chart = entity_create('chart', array('type' => $chart->type)); 
  }
  else {
    drupal_set_title(t('Edit !title', array('!title' => $chart->title)));
  }
  $form_state['storage'] = array('chart' => $chart);
  wac_chart_base_form($form, $form_state);
  field_attach_form('chart', $chart, $form, $form_state);
  if (!empty($form['data_file'])) {
    foreach ($form['data_file'][LANGUAGE_NONE] as $key => $file_field) {
      if (is_numeric($key)) {
        $form['data_file'][LANGUAGE_NONE][$key]['#process'][] = 'wac_file_field_process';
      }
    }
  }
  return $form;
}

function wac_chart_base_form(&$form, $form_state) {
  $chart = $form_state['storage']['chart'];
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title:'),
    '#required' => TRUE,
    '#default_value' => !empty($chart->title) ? $chart->title : '',
    '#weight' => -1
  );
  $form['status'] = array(
    '#type' => 'checkbox',
    '#title' => t('Published'),
    '#description' => t('Should this chart be publicly available?'),
    '#default_value' => !empty($chart->status) ? $chart->status : 1,
    '#weight' => 10
  );
  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 11
  );
  if (!empty($chart) && empty($chart->is_new)) {
    $form['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#submit' => array('wac_chart_delete_submit'),
      '#weight' => 12
    );
  }
  $form['#validate'] = array('wac_chart_validate');
  $form['#submit'] = array('wac_chart_submit');
}

function wac_chart_validate($form, &$form_state) {
  $chart = $form_state['storage']['chart'];
  field_attach_form_validate('chart', $chart, $form, $form_state); 
}

function wac_chart_submit($form, $form_state) {
  dsm($form_state);
  $chart = $form_state['storage']['chart'];
  $chart->title = $form_state['values']['title'];
  $chart->status = $form_state['values']['status'];
  global $user;
  $chart->uid = $user->uid; 
  if (!empty($chart->is_new)) {
    $chart->created = time();
  } 
  $chart->save(); 
  drupal_goto('chart/' . $chart->cid);
}

function wac_chart_delete_submit($form, $form_state) {
  $chart = $form_state['storage']['chart'];
  $options = array('query' => array('wac_from' => 'chart/' . $chart->cid . '/edit'));
  drupal_goto('chart/' . $chart->cid . '/delete', $options);
}

function wac_chart_delete_confirm($form = array(), $form_state, $chart) {
  if (is_object($chart)) {
    $path = !empty($_GET['wac_from']) ? $_GET['wac_from'] : 'chart/' . $chart->cid . '/edit';
    $question = t('Are you sure you want to delete: !title', array('!title' => $chart->title));
    $form['#submit'] = array('wac_chart_delete_confirm_submit');
    $form['chart'] = array(
      '#type' => 'hidden',
      '#value' => json_encode($chart)
    );
    return confirm_form($form, $question, $path);
  }
  else {
    drupal_set_message(t('There has been an error. This chart has already been deleted.'), 'error');
    return $form;
  }
}

function wac_chart_delete_confirm_submit($form, $form_state) {
  $chart = json_decode($form['chart']['#value']);
  wac_chart_entity_delete($chart); 
}

function wac_file_field_process($element, &$form_state, $form) {
  if (!empty($element['upload_button'])) {
    $element['upload_button']['#ajax']['path'] = str_replace('file/ajax', 'wac/file/ajax', $element['upload_button']['#ajax']['path']);
  }
  return $element;
}