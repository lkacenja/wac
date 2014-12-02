<?php

function wac_chart_add_page() {
  $bundles = wac_get_chart_types();
  $links = array();
  foreach ($bundles AS $bundle => $item) {
    $links[] = l($item['title'], 'chart/add/' . $bundle) . '<p>' .$item['description'] . '</p>';
  }
  return array('#theme' => 'item_list','#items' => $links);
}

function wac_admin_charts() {
  $header = array(
    array('data' => t('Title'), 'field' => 'title'),
    array('data' => t('Status'), 'field' => 'status'),
    array('data' => t('Type'), 'field' => 'type'),
    array('data' => t('Created'), 'field' => 'created', 'sort' => 'asc'),
    array('data' => t('Operations')),
  );
  $query = db_select('wac', 'w')->extend('TableSort')->extend('PagerDefault')->limit(25);
  $query->fields('w', array('cid', 'title', 'status', 'type', 'created'));
  $query->orderByHeader($header);
  $result = $query->execute();
  $rows = array();
  $options = array('query' => array('destination' => $_GET['q']));
  foreach ($result as $row) {
    $data = array(
      l($row->title, 'chart/' . $row->cid),
      $row->status == 1 ? 'published' : 'not published',
      $row->type,
      date('m/d/Y g:i', $row->created),
      l(t('Edit'), 'chart/' . $row->cid . '/edit', $options) . ' ' . l(t('Delete'), 'chart/' . $row->cid . '/delete', $options)
    );
    $rows[] = array('data' => $data);
  }
  $make = l(t('Make one now.'), 'chart/add');
  $output = array();
  $output['table'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#empty' => t('No charts have been created yet. !make', array('!make' => $make)),
  );
  $output['table_pager'] = array('#theme' => 'pager');
  return $output;
}

function wac_chart_admin_types_page() {
  if (!module_exists('field_ui')) {
    return "Enable Field UI module for more options.";
  } 
  $bundles = wac_get_chart_types();
  $header = array('Title', 'Operations');
  $rows = array();
  foreach ($bundles AS $key => $bundle) {
    $rows[] = array(
      $bundle['title'],
      l('Manage Fields', 'admin/structure/chart/manage/' . $key  . '/fields') . ' | ' . l('Manage Display', 'admin/structure/chart/manage/' . $key . '/display')
    );
  }
  $output['table'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
  );
  return $output;
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
  if (user_access('administer web accessible charts') || user_access('publish web accessible charts')) {
    $form['status'] = array(
      '#type' => 'checkbox',
      '#title' => t('Published'),
      '#description' => t('Should this chart be publicly available?'),
      '#default_value' => isset($chart->status) ? $chart->status : 1,
      '#weight' => 10
    );
  }
  else {
    $form['status'] = array(
      '#type' => 'hidden',
      '#value' => FALSE
    );
  }
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
