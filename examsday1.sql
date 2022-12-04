SELECT lunch,
AVG(writing_score) AS "Average Writing"
FROM exams
GROUP BY lunch;
