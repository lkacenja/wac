(function ($, Drupal, window, document, undefined) {
  Drupal.behaviors.Wac = {
    attach: function() {
      if (Drupal.settings.wac) {
        for (var x in Drupal.settings.wac) {
          $("#" + Drupal.settings.wac[x].id).once('wac-chart',
            function() {
              var chart;
              if (Drupal.Wac[Drupal.settings.wac[x].class]) {
                chart = new Drupal.Wac[Drupal.settings.wac[x].class](Drupal.settings.wac[x]);
                chart.setup();
                chart.render();
              }
            }
          );
        }
      }
    },
    detach: function() {

    }
  };
})(jQuery, Drupal, this, this.document);
