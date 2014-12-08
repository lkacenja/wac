(function (Class, Drupal) {
  if (Drupal.ahahError) {
    // Drupal 6
    Drupal.behaviors.wac = init; 
  }
  else {
    // Drupal 7+
    Drupal.behaviors.wac = {
      attach: init
    };
  }
  function init() {
    if (Drupal.settings.wac) {
      var x, element, chart;
      for (var x in Drupal.settings.wac) {
          element = document.getElementById(Drupal.settings.wac[x].id);
        if ((' ' + element.className + ' ').indexOf(' ' + 'wac-chart-processed' + ' ') < 0) {
          chart = new Drupal.Wac[Drupal.settings.wac[x].class](Drupal.settings.wac[x]);
          chart.setup();
          chart.render();
          element.className += ' wac-chart-processed';
        }
      }
    }
  }
})(Class, Drupal);
