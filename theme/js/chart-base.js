(function (Class, Drupal) {
  // Establish namespace
  Drupal.Wac = Drupal.Wac || {};
  // Provide base chart class
  Drupal.Wac.Chart = Class.extend({
    el: null,
    svg: null,
    data: null,
    header: null,
    dictionary: null,
    init: function(data) {
      var msg, element, header, x;
      if (!data) {
        msg = "A Data object {id, dictionary, data} must be supplied to a chart.";
      }
      if (data && !data.id) {
        msg = "Data object must have an id key.";
      }
      if (data && !data.dictionary) {
        msg = "Data object must have a dictionary key.";
      }
      if (data && !data.data) {
        msg ="Data object must have a data key."
      }
      if (msg) {
        throw new Error(msg);
      }
      element = document.getElementById(data.id);
      this.el = d3.select(element);
      this.data = data.data;
      header = this.data.shift(); 
      this.header = {};
      for (x in header) {
        this.header[header[x]] = x;
      }
      this.dictionary = data.dictionary;
    },
    setup: function() {
      // Define alterable things like scales and axes.
      // Also build svg.
      this.svg = this.el.append("svg");
      // Append title and description if they exist.
      // Screen readers ideally first read these fields and then proceed to the data alt
      if (this.dictionary.title) {
        this.svg.append('title').text(this.dictionary.title);
      }
      if (this.dictionary.alternate_description) {
        this.svg.append('desc').text(this.dictionary.alternate_description);
      }
    },
    render: function() {
      // Actually create the visualization.
    },
    clearSVG: function() {
      this.svg.selectAll("*").remove(); 
    }
  });
})(Class, Drupal);
