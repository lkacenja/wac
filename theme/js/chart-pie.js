(function (Class, Drupal) {
  /**
   * Class to render a super simple pie chart.
   */
  Drupal.Wac.ChartPie = Drupal.Wac.Chart.extend({
    width: null,
    height: null,
    margin: null,
    radius: null, 
    arc: null,
    pie: null,
    setup: function() {
      // Call parent setup to get svg
      this._super();
      // SVG dimensions
      this.margin = {top: 10, right: 10, bottom: 10, left: 10};
      this.width = parseInt(this.el.style('width'), 10) - this.margin.left - this.margin.right;
      this.height = parseInt(this.el.style('height'), 10) - this.margin.top - this.margin.bottom;
      this.svg.attr("width", this.width + this.margin.left + this.margin.right)
        .attr("height", this.height + this.margin.top + this.margin.bottom);
      // Easy access keys
      this.dataKey = this.header[this.dictionary.value[0]],
      this.labelKey = this.header[this.dictionary.pie_label[0]],
      this.altKey = this.header[this.dictionary.data_field[0]];
      // Radius
      this.radius = Math.min(this.width, this.height) / 2;
      this.setupPie(); 
    },
    setupPie: function() {
      var arcs, 
        _this = this;
      // Store arc
      this.arc = d3.svg.arc()
        .outerRadius(this.radius - 10)
        .innerRadius(0);
      // Create the pie layout object we will use during render.
      this.pie = d3.layout.pie()
        .sort(null)
        .value(function(d) { return d[_this.dataKey]; });
      // Create scale for generating classes
      this.scale = d3.scale.ordinal()
        .domain(d3.extent(function(d) {return d[_this.dataKey]; }))
        .range(d3.range(this.data.length).map(function(i) { return "arc-" + i; }));
    },
    render: function() {
      var _this = this;
      // Offset wrapper including margins
      this.offsetWrapper = this.svg.append("g")
        .attr("transform", "translate(" + ((this.width / 2) + this.margin.left) + "," + ((this.height / 2 ) + this.margin.top) + ")"); 
      // Make sure chart vals are positive.
      this.data.forEach(function(d) {
        d[_this.dataKey] = +d[_this.dataKey];
      });
      // Arcs
      arcs = this.offsetWrapper.selectAll('.arc')
        .data(this.pie(this.data))  
        .enter().append("g")
        .attr("class", "arc-wrapper");
      arcs.append("path")
        .attr("d", this.arc)
        .attr("class", function(d) {
          var classes = ["arc"];
          classes.push(_this.scale(d.data[_this.dataKey]));
          return classes.join(" ");
        })
        .attr("aria-labelledby", "title desc")
        .append("title").text(
          function(d) {
            return d.data[_this.altKey];
          }
        )
        .attr('aria-label',
          function(d) {
            return d.data[_this.altKey];
          }
        );
      arcs.selectAll(".arc")
        .append("desc");
      arcs.append("text")
        .attr("transform", function(d) { return "translate(" + _this.arc.centroid(d) + ")"; })
        .attr("dy", ".35em")
        .style("text-anchor", "middle")
        .text(function(d) { return d.data[_this.labelKey]; })
        .attr("aria-hidden", "true");
    }
  });
})(Class, Drupal);
