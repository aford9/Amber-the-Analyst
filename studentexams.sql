-- Data Cleaning and Validation
-- Prior to beginning my queries, I changed the column names to be more SQL friendly
/* ALTER TABLE ‘examdata’, ‘exams’
CHANGE COLUMN ‘race/ethnicity’ ‘race’ TEXT NULL DEFAULT NULL,
CHANGE COLUMN ‘parental level of education’ ‘parental_education’ TEXT NULL DEFAULT NULL,
CHANGE COLUMN ‘test preparation course’ ‘test_prep’ TEXT NULL DEFAULT NULL,
CHANGE COLUMN ‘math score’ ‘math_score’ INT NULL DEFAULT NULL,
CHANGE COLUMN ‘reading score’ ‘reading_score’ INT NULL DEFAULT NULL,
CHANGE COLUMN ‘writing score’ ‘writing_score’ INT NULL DEFAULT NULL; */

SELECT * 
FROM exams
LIMIT 10;

/* Results 
gender	  race	     parental_education	     lunch	       test_prep	  math_score  reading_score	 writing_score
--------+-----------+-------------------+---------------+--------------+-------------+--------------+--------------
male	|group A	|high school	    |standard	    |completed	   |67				|67				|63
female	|group D	|some high school   |free/reduced	|none	       |40				|59				|55
male	|group E	|some college	    |free/reduced	|none	       |59				|60				|50
male	|group B	|high school	    |standard	    |none	       |77				|78				|68
male	|group E	|associate's degree	|standard	    |completed	   |78				|73				|68
female	|group D	|high school	    |standard	    |none	       |63				|77				|76
female	|group A	|bachelor's degree	|standard	    |none	       |62				|59				|63
male	|group E	|some college	    |standard	    |completed	   |93				|88				|84
male	|group D	|high school	    |standard	    |none	       |63				|56				|65
male	|group C	|some college	    |free/reduced	|none	       |47				|42				|45 */

/* This data appears to be from a survey or form and the responses look consistent when briefly looking over the data. 
To ensure that there are no invalid data values, I will be performing a simple check of each column. 
For example, my gender column should only contain values of male and female. If there are other values or something 
is misspelled this will need to be adjusted to ensure accurate results when completing the analysis. For the integer 
values our validation check will be based on the type of data we’re collecting. Test scores shouldn’t be negative or 
above 100%, therefore we will check for these types of scores when validating. */

SELECT gender,
COUNT(*) AS 'Total'
FROM exams
GROUP BY gender;

/* Results
gender Total
------+------
male  | 517
female| 483   */

SELECT race,
COUNT(*) AS 'Total'
FROM exams
GROUP BY race;

/* Results
race      Total
--------+------
group A  | 79
group D  | 262
group E  | 131
group B  | 205
group C  | 323   */

SELECT lunch,
COUNT(*) AS 'Total'
FROM exams
GROUP BY lunch;

/* Results
lunch        Total
------------+------
standard    | 652
free/reduced| 348  */

SELECT test_prep,
COUNT(*) AS 'Total'
FROM exams
GROUP BY test_prep;

/* Results
test_prep     Total
----------+------
completed | 335
none      | 665  */

SELECT COUNT(reading_score) AS 'Invalid Total'
FROM exams
WHERE reading_score > 100 OR reading_score < 0;

/* Results
Invalid Total
-------------+
	0           */
    
SELECT COUNT(math_score) AS 'Invalid Total'
FROM exams
WHERE math_score > 100 OR math_score < 0;

/* Results
Invalid Total
-------------+
	0           */
    
SELECT COUNT(writing_score) AS 'Invalid Total'
FROM exams
WHERE writing_score > 100 OR writing_score < 0;

/* Results
Invalid Total
-------------+
	0           */

-- EXPLORATORY ANALYSIS

-- First, I’m going to see what the average test scores are for each subject
SELECT AVG(math_score) AS 'AVG Math, Reading, Writing'
FROM exams
UNION
SELECT AVG(reading_score)
FROM exams
UNION
SELECT AVG(writing_score)
FROM exams;

/* Results
AVG Math, Reading, Writing
--------------------------+
			66.3960
            69.0020
            67.7380      */
-- The scores don't have a major deviation between one another and on average all students are scoring below a C

-- Next, let’s look at how these scores compare for boys and girls in each subject.

SELECT gender,
AVG(math_score) AS 'Average Math'
FROM exams
GROUP BY gender;

/* Results
gender Average Math
------+-------------
male  | 69.3849
female| 63.1967  */

SELECT gender,
AVG(reading_score) AS 'Average Reading'
FROM exams
GROUP BY gender;

/* Results
gender Average Reading
------+-------------
male  | 66.3056
female| 71.8882  */

SELECT gender,
AVG(writing_score) AS 'Average Writing'
FROM exams
GROUP BY gender;

/* Results
gender Average Writing
------+---------------
male  | 64.0290
female| 71.7081  */

/* Girls are outperforming boys in reading and writing, while boys outperform girls in math. Teachers
should ensure all students in their class have a clear understaning of objectives before moving on to
a new topic. For group activities, the teacher should combine both genders in small groups so students
can help each other grasp challenging topics. */

/* Now I’m going to see how test preparation courses affected the student’s scores. Based on the queries 
below there is a positive correlation between completion of test prep courses and students’ exam scores 
in all subjects. */

SELECT test_prep,
AVG(writing_score) AS 'Average Writing'
FROM exams
GROUP BY test_prep;

/* Results
test_prep Average Writing
---------+---------------
completed| 74.6716
none     | 64.2451  */

SELECT test_prep,
AVG(math_score) AS 'Average Math'
FROM exams
GROUP BY test_prep;

/* Results
test_prep Average Math
---------+------------
completed| 69.6866
none     | 64.7383  */

SELECT test_prep,
AVG(reading_score) AS 'Average Reading'
FROM exams
GROUP BY test_prep;

/* Results
test_prep Average Reading
---------+---------------
completed| 74.0896
none     | 66.4391  */

/* Next, I’m performing queries to determine the effect a parent’s education level has on test scores. Based on the data, 
it appears that parental education directly effects a student’s test performance. The more education a student’s parent
has, the higher they score on exams in all areas. */

SELECT parental_education,
AVG(reading_score) AS 'Average Reading'
FROM exams
GROUP BY parental_education;

/* Results
parental_education Average Reading
------------------+---------------
some high school  | 64.4084
high school       | 67.4010 
some college      | 68.0450
associate's degree| 70.9852
bachelor's degree | 74.0089
master's degree   | 75.4286
*/

SELECT parental_education,
AVG(writing_score) AS 'Average Writing'
FROM exams
GROUP BY parental_education;

SELECT parental_education,
AVG(math_score) AS 'Average Math'
FROM exams
GROUP BY parental_education;

/* Now I’m going to analyze how socioeconomic factors effect student’s exam scores. 
I will do this by exploring the test scores of students who receive free/reduced lunch. */

SELECT lunch,
AVG(math_score) AS 'Average Math'
FROM exams
GROUP BY lunch;
/* Results
lunch     Average Math
---------+------------
standard    | 70.6074
free/reduced| 58.5057  */

SELECT lunch,
AVG(reading_score) AS 'Average Reading'
FROM exams
GROUP BY lunch;
/* Results
lunch     Average Reading
---------+------------
standard    | 72.1043
free/reduced| 63.1897  */

SELECT lunch,
AVG(writing_score) AS 'Average Writing'
FROM exams
GROUP BY lunch;
/* Results
lunch     Average Writing
---------+------------
standard    | 71.3742
free/reduced| 60.9253  */

/* There is an alarming difference in the test scores of students who receive free or reduced lunch.
Teachers should do their best to eliminate bias when teaching their curriculum and offer support for all 
of their students regardless of economic status. Students may need more tutoring options and hands on support
to address this disparity.   */

-- Final recommendations will be available on the tableau dashboard for this dataset