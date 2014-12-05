Drupal = window.Drupal || {};
(function(Drupal) {
  Drupal.settings = Drupal.settings || {};
  Drupal.behaviors = Drupal.settings || {};
  files = <?php print $elements['#files']; ?>,
  lcount = 0,
  fcount = files.length;
  Drupal.settings.wac = <?php print $elements['#settings']; ?>;
  function loadFile(url, callback) {
    var element = document.getElementsByTagName('head')[0],
      asset,
      ext = fileGetExtension(url);
    if (ext == 'js') {
      asset = document.createElement('script');
      asset.type = 'text/javascript';
      asset.src = url;
    }
    if (ext == 'css') {
      asset = document.createElement('link');
      asset.rel = 'stylesheet';
      asset.type = 'text/css';
      asset.media = 'all';
      asset.href = url;
    }
    asset.onreadystatechange = callback;
    asset.onload = callback;
    element.appendChild(asset); 
  }
  function fileGetExtension(url) {
    var bits = url.split('.');
    return bits.pop();
  }
  function checkLoad() {
    lcount ++;
    if (lcount == fcount) {
      init();
    }
    else {
      loadFile(files[lcount], checkLoad);
    }
  }
  function init() {
    Drupal.behaviors.Wac.attach(); 
  }
  document.addEventListener('DOMContentLoaded', function(event) {
    loadFile(files[0], checkLoad); 
  }); 
})(Drupal);
