<h2 id="overview">Overview</h2>
<p>The Web Accessible Charts (WAC) module is an attempt to make simple, accessible charts easy to make. The module provides a chart entity which may be created on the <a href='/chart/add'>chart add page</a> and administered from the <a href="/admin/content/charts">chart admin page</a> (permissions allowing). Charts are visualized using the <a href="http://d3js.org">Data Driven Documents (D3)</a> library and SVG. WAC currently supports simple bar, pie and line charts. If you are using this website to create charts, more help information is provided in the <a href="#creating">Creating a Chart</a> and <a href="#data">Data: Charting Successfully</a> sections below. If you are a developer, try reading the readme file in the module's root or the main <a href="https://github.com/lkacenja/wac" target=_"blank">Github page</a> for tips on implementation.</p>
<h2 id="accessibility">Accessibility Approach</h2>
<p>The goal of this module is not to create extensively complicated or aesthetically mind blowing charts that D3 is certainly capable of. It is to empower everyday website users to create simple charts that are more audience inclusive than other solutions. Hopefully, the charts created add meaning and richness of experience not always available for all users. WAC attempts to implement the Web Accessible Initiative's Accessible Rich Internet Applications Suite (ARIA) on scaleable vector graphics (SVG) produced by D3. To create a chart, users are required to provide alternate title and descriptions, as well as alternate text for each data point to be visualized. This aids screen reader software in providing meaning to the user. Rather that the audio label of "graphic", the user will ideally experience something more along the lines of "Frequency of Letters in the English Language: This chart shows how often the letters of the alphabet are used in English language words. The Letter A is used in 8% of words. The Letter B is used in 14% of words. etc".</p>
<p>WAC has been tested with the following results on the devices and software below:</p>
<h3>PC Internet Explorer 9 Running JAWS</h3>
<p>Works very well. The user gets a clear audio readout of the title, description of the chart and key data points.</p>
<h3>PC Internet Explorer 9 Running NVDA</h3>
<p>Works a little less well than JAWS, but still gives a very nice clear readout of the title, description of the chart and key data points.</p>
<p>NB: JAWS and NVDA seem to have very limited support working with other browsers natively. Had trouble getting either to work well in Google Chrome.</p>
<h3>PC/MAC ChromeVox Google Chrome</h3>
<p>Works very well. All chart features are readout.</p>
<h3>Apple VoiceOver Safari</h3>
<p>Only allows for a single alternative text field, describing the chart.</p>
<p>Other devices and software may work with varying success.</p>
<p>WAC implements a high contrast color scheme with large fonts in attempts to accommodate colorblind and sight impaired users.</p>
<h2 id="creating">Creating a Chart</h2>
<p>To create a chart visit the <a href='/chart/add'>chart add page</a>. If you receive a 403 access denied message, this website's permissions are not configured in a manner that allow you to add charts at this time. Please contact a site administrator. Creating a chart requires an alternative title, description, a dataset to visualize and alternative text for each data point.</p>
<p>Title and descriptions should semantically and aesthetically describe the chart. What does the chart show visually? What does the chart mean? Why is it important?</p>
<p>NB: Title and description fields may not be displayed for non-assitive devices.</p>
<p>Datasets may be uploaded as files. Comma Separated Value (CSV), Tab Separated Value (TSV) and Javascript Simple Object Notation (JSON) files are currently supported. Most spreadsheet applications or database software will export using one of these formats. For CSV and TSV files headers are expected to be the first line of the file. Data values should be raw without any markers like "$" or "%".</p>
<p>Below is a functional CSV snippet:<p>
<pre>
Letter,Frequency,Alt
A,.08167,A is used in approximately 8% of English words
B,.01492,B is used in approximately 14% of English words
C,.02782,C is used in approximately 2% of English words
</pre>
<p>The nature of your data is essential to deciding what kind of chart to use. Each chart leverages different fields to create the final visualization. Below is a description of the supported types of chart, their fields and their application.</p>
<h3>Bar Charts</h3>
<p>A bar graph is a chart that uses either horizontal or vertical bars to show comparisons among categories. One axis of the chart shows the specific categories being compared, and the other axis represents a discrete value.</p>
<p>The bar chart form has special fields for X Axis, Y Axis, Alternate Data Field and Value Format. The X Axis field is anticipated to be ordinal. That is non-scaler, arbitrary data i.e. (A, B, C, D). The Y Axis field is anticipated to be linear or scaler (i.e. .08167, .01492, .02782). The Alt field is used to store alternate data for each intersection of the x and y axes (i.e. A is used in approximately 8% of English words). These fields should contain the matching header label or JSON object key for their column or property in the data.</p>
<p>The Value Format field expresses how to interpret the data. Currently numeric, percent and US dollars are supported. Numeric format will not format the y axis values. Percent format anticipates percents as decimal values, which are then converted and formatted accordingly. US dollar format expects dollars and cents formatted (x.xxx) data that is then formatted ($x.xx).</p>
<h3>Line Charts</h3>
<h3>Pie Charts</h3>
<p>A pie chart (or a circle chart) is a circular statistical graphic, which is divided into sectors to illustrate numerical proportion.</p>
<p>The pie chart form has special fields for Value, Label and Alternate Data Field. The Value field is used to determine numerical proportion (i.e. .08167, .01492, .02782). The Label field is placed on top of the slice (i.e. A, B, C, D). The Alt field is used to store alternate data for each slice (i.e. A is used in approximately 8% of English words).</p>
<h2>Data: Charting Successfully</h2>
<p>If you attempted to create a chart and it doesn't work at all, looks strange or is out of proportion, there is likely an issue with your data. To be safe, first ensure that the appropriate key fields (axes and value fields) match your data's header or JSON object keys exactly. Next, ensure that the columns you've selected are the correct type for the chart (i.e. Bar chart Y Axis field is a numeric or decimal value). Read the chart field descriptions in the <a href="#creating">Creating a Chart</a> section for more information.</p> 
<p>If your chart is not displaying at all, try working with a smaller dataset and modifying values until you get the anticipated result. Then, apply findings to the whole set. If your chart looks strange or out of proportion, ensure that you've used the appropriate type of chart for your data (i.e. pie charts do not excel at showing change over time). If your data's extents are extremely disparate in range, you may want to consider removing that column or row. Also, you may need to use a data optimization method like Jenks Natural Breaks, Quantiles etc.</p>
