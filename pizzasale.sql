/* First I'm going to view the data from each table and create a database schema to 
visualize how the tables are connected. If you want to view my schema along with a detailed description of
the project and results, check out my portfolio website. */

SELECT * FROM orders;

SELECT * FROM order_details;

SELECT * FROM pizzas;

/* Now, we want to see what the 10 busiest days are for this pizza company. We can achieve this by selecting the
10 dates with the most orders. */

SELECT date
FROM orders
GROUP BY date
ORDER BY COUNT(*) DESC
LIMIT 10;

/* Result:
    date
+-----------+
'2015-11-27'
'2015-11-26'
'2015-10-15'
'2015-07-04'
'2015-05-15'
'2015-07-03'
'2015-02-01'
'2015-10-01'
'2015-07-17'
'2015-08-14'
*/

/* Not only is it important we know when the pizza store is selling the most, the marketing team 
wants a list of some of the slowest sales days of the year so they can run promotions during this 
time and increase overall sales for the restaurant */

SELECT date
FROM orders
GROUP BY date
ORDER BY COUNT(*) ASC
LIMIT 20;

/* Result:
    date
+-----------+
'2015-12-29'
'2015-12-30'
'2015-12-27'
'2015-03-22'
'2015-02-22'
'2015-12-26'
'2015-12-28'
'2015-07-05'
'2015-08-30'
'2015-10-11'
'2015-11-22'
'2015-01-25'
'2015-10-25'
'2015-10-18'
'2015-11-15'
'2015-06-28'
'2015-05-19'
'2015-11-18'
'2015-11-29'
'2015-09-06'
*/

/* I'm performing a query to see which pizzas had the most orders. This query is
specifically pulling the top 10 types of pizzas ordered.  */
SELECT pizza_id,
COUNT(*) AS 'Total'
FROM order_details
GROUP BY pizza_id
ORDER BY COUNT(*) DESC
LIMIT 10;

/* Results

pizza_id       total
--------------+-----
big_meat_s    1811
thai_ckn_l    1365
five_cheese_l 1359
four_cheese_l 1273
classic_dlx_m 159
spicy_ital_l  1088
hawaiian_s    1001
southw_ckn_l  993
bbq_ckn_l     967
bbq_ckn_m     926
*/

/* Similar to the last query we want to see the 10 types of pizza customers ordered the least */
SELECT pizza_id,
COUNT(*) AS 'Total'
FROM order_details
GROUP BY pizza_id
ORDER BY COUNT(*) ASC
LIMIT 10;

/* Results

pizza_id       total
--------------+-----
the_greek_xxl   28
green_garden_l  94
ckn_alfredo_s   96
calabrese_s     99
mexicana_s      160
ckn_alfredo_l   187
ital_veggie_l   190
ital_supr_s     194
the_greek_l     255
spinach_supr_m  266
*/

/* We're going to run a query that shows us the order details of the 10 most expensive orders 
at the pizza shop. Additionally, we're going to create a new column to display the order total. The quantity and price 
columns came from 2 different tables, so a join function was performed. */
SELECT *,
pizzas.price * order_details.quantity AS 'Total'
FROM pizzas
JOIN order_details 
ON pizzas.pizza_id = order_details.pizza_id
ORDER BY Total DESC
LIMIT 10;
/* Results

pizza_id	pizza_type_id  size	price	order_details_id	order_id	pizza_id	quantity	Total
cali_ckn_l	    cali_ckn	L	20.75	35497	              15674	    cali_ckn_l	    4	    83
bbq_ckn_l	    bbq_ckn	    L	20.75	38820	              17112	    bbq_ckn_l	    3	    62.25
prsc_argla_l    prsc_argla	L	20.75	37639	              16619	    prsc_argla_l	3	    62.25
thai_ckn_l	    thai_ckn	L	20.75	18318	              8040	    thai_ckn_l	    3	    62.25
spicy_ital_l	spicy_ital	L	20.75	184	                  78	    spicy_ital_l	3	    62.25
ital_cpcllo_l	ital_cpcllo	L	20.5	35628	              15728	    ital_cpcllo_l	3	    61.5
five_cheese_l	five_cheese	L	18.5	41559	              18286	    five_cheese_l	3	    55.5
the_greek_xl	the_greek	XL	25.5	45520	              19988	    the_greek_xl	2	    51
the_greek_xl	the_greek	XL	25.5	21608	              9483	    the_greek_xl	2	    51
the_greek_xl	the_greek	XL	25.5	46789	              20543	    the_greek_xl	2	    51 */


/* I'm going to perform a query to determine which size pizza customers order the most. */
SELECT size, COUNT(size) AS 'Total'
FROM pizzas
JOIN order_details 
ON pizzas.pizza_id = order_details.pizza_id
GROUP BY size
ORDER BY Total DESC;

/* Results
size Total
L    18526
M    15385
S    14137
XL   544
XXL  28
*/
-- Check out the full analysis and dashboard on my website linked in the "About me" section