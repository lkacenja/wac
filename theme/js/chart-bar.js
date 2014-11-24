(function ($, Drupal, window, document, undefined) {
  /**
   * Class to create a very basic bar chart.
   *   Class presumes an ordinal, bottom x axis and a linear left y axis.
   */
  Drupal.Wac.ChartBar = Drupal.Wac.Chart.extend({
    x: null,
    y: null,
    xAxis: null,
    yAxis: null,
    width: null,
    height: null,
    margin: null,
    setup: function(data) {
      // Call the base classes setup defining the svg.
      this._super();
      // Set svg width/height 
      this.margin = {top: 0, right: 0, bottom: 25, left: 40};
      this.width = parseInt(this.el.style('width'), 10) - this.margin.left - this.margin.right;
      this.height = parseInt(this.el.style('height'), 10) - this.margin.top - this.margin.bottom;
      this.svg.attr("width", this.width + this.margin.left + this.margin.right)
        .attr("height", this.height + this.margin.top + this.margin.bottom); 
      // Set up axes and scales
      this.setupX(); 
      this.setupY();
    },
    setupX: function() {
      var _this = this;
      this.x = d3.scale.ordinal()
        .rangeRoundBands([0, this.width], .1)
        .domain(this.data.map(function(d) {
          var key = _this.header[_this.dictionary.x_axis[0]];
          return d[key];
        }));
      this.xAxis = d3.svg.axis()
        .scale(this.x)
        .orient("bottom");
    },
    setupY: function() {
      var _this = this;
      this.y = d3.scale.linear()
        .range([this.height, 0])
        .domain([0, d3.max(this.data, function(d) {
          var key = _this.header[_this.dictionary.y_axis[0]];
          return parseFloat(d[key]);
        })]);
      this.yAxis = d3.svg.axis()
        .scale(this.y)
        .orient("left");
    },
    render: function() {
      var _this = this;
      this.offsetWrapper = this.svg.append("g")
        .attr("transform", "translate(" + this.margin.left + "," + this.margin.top + ")");
      // Axes
      this.offsetWrapper.append("g")
        .attr("class", "axis x-axis")
        .attr("transform", "translate(0," + this.height + ")")
        .call(this.xAxis);
      this.offsetWrapper.append("g")
        .attr("class", "axis y-axis")
        .call(this.yAxis);
      // Data
      this.offsetWrapper.append("g")
        .attr("class", "content")
        this.offsetWrapper.selectAll('.bar')
        .data(this.data)
        .enter()
        .append("rect")
        .attr("x", function(d) { 
          var key = _this.header[_this.dictionary.x_axis[0]];
          return _this.x(d[key]);
        })
        .attr("width", this.x.rangeBand())
        .attr("y", function(d) {
          var key = _this.header[_this.dictionary.y_axis[0]];
          return _this.y(d[key]);
        })
        .attr("height", function(d) {
          var key = _this.header[_this.dictionary.y_axis[0]];
          return _this.height - _this.y(d[key]); 
        })
        .attr("aria-labelledby", "title desc")
        .append("title").text(
          function(d) {
            var key = _this.header[_this.dictionary.data_field[0]];
            return d[key];
          }
        )
        .attr('aria-label',
          function(d) {
            var key = _this.header[_this.dictionary.data_field[0]];
            return d[key];
          }
        );
    } 
  });
})(jQuery, Drupal, this, this.document);
