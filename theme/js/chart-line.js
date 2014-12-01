(function ($, Drupal, window, document, undefined) {
  /**
   * Class to create a very basic line chart.
   *   Class presumes an ordinal, bottom x axis and a linear left y axis.
   */
  Drupal.Wac.ChartLine = Drupal.Wac.Chart.extend({
    x: null,
    y: null,
    xAxis: null,
    yAxis: null,
    width: null,
    height: null,
    margin: null,
    xKey: null,
    yKey: null,
    altKey: null,
    setup: function() {
      this._super();
      // Set svg width/height 
      this.margin = {top: 10, right: 0, bottom: 25, left: 50};
      this.width = parseInt(this.el.style('width'), 10) - this.margin.left - this.margin.right;
      this.height = parseInt(this.el.style('height'), 10) - this.margin.top - this.margin.bottom;
      this.svg.attr("width", this.width + this.margin.left + this.margin.right)
        .attr("height", this.height + this.margin.top + this.margin.bottom);
      // Easy access keys
      this.xKey = this.header[this.dictionary.x_axis[0]],
      this.yKey = this.header[this.dictionary.y_axis[0]],
      this.altKey = this.header[this.dictionary.data_field[0]];
      // Set up axes and scales
      this.setupX();
      this.setupY(); 
      this.setLine();
    },
    setupX: function() {
      var _this = this;
      this.x = d3.scale.ordinal()
        .rangePoints([0, this.width])
        .domain(this.data.map(function(d) {
          return d[_this.xKey];
        })); 
      this.xAxis = d3.svg.axis()
        .scale(this.x)
        .orient("bottom");
    },
    setupY: function() {
      var formatter,
        _this = this,
        format = this.dictionary.value_format[0];
      this.y = d3.scale.linear()
        .range([this.height, 0]);
      this.yAxis = d3.svg.axis()
        .orient("left");
      switch(format) {
        case 'percent':
          this.y.domain([0, 1]);
          this.yAxis.ticks(10, "%");
          break;
        case 'us_dollars':
          formatter = d3.format("$,.2f");
          this.yAxis.tickFormat(formatter);
          this.y.domain([0, d3.max(this.data, function(d) {
            return parseFloat(d[_this.yKey]);
          })]);
          break;
        default:
          this.y.domain([0, d3.max(this.data, function(d) {
            return parseFloat(d[_this.yKey]);
          })]);
          break;
      }
      this.yAxis.scale(this.y); 
    },
    setLine: function() {
      var _this = this;
      this.line = d3.svg.line()
        .x(function(d) { return _this.x(d[_this.xKey]); })
        .y(function(d) { return _this.y(d[_this.yKey]); });
    },
    render: function() {
      var _this = this;
      this.offsetWrapper = this.svg.append("g")
        .attr("transform", "translate(" + this.margin.left + "," + this.margin.top + ")");
      this.offsetWrapper.append("g")
        .attr("class", "axis-x axis")
        .attr("transform", "translate(0," + this.height + ")")
        .call(this.xAxis)
        .attr("aria-hidden", "true"); 
      this.offsetWrapper.append("g")
        .attr("class", "axis-y axis")
        .call(this.yAxis)
        .attr("aria-hidden", "true"); 
      this.offsetWrapper.append("path")
        .datum(this.data)
        .attr("class", "line")
        .attr("d", this.line); 
        this.offsetWrapper.selectAll('.point')
        .data(this.data)
        .enter()
        .append("circle")
        .attr("class", "point")
        .attr("cx", function(d) {
          return _this.x(d[_this.xKey]);
        })
        .attr("cy", function(d) {
          return _this.y(d[_this.yKey]);
        })
        .attr("r", 3)
        .attr("aria-labelledby", "title desc")
        .append("title").text(
          function(d) {
            return d[_this.altKey];
          }
        )
        .attr('aria-label',
          function(d) {
            return d[_this.altKey];
          }
        );
      this.offsetWrapper.selectAll(".point")
        .append("desc");
    }   
  });
})(jQuery, Drupal, this, this.document);
