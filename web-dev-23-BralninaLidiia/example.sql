-- создание таблицы names для хранения имен пользователей
CREATE TABLE names (
    id SERIAL PRIMARY KEY,  -- id
    name VARCHAR(50) UNIQUE -- уникальное имя
);

-- создание таблицы comments для хранения комментариев
CREATE TABLE comments (
    id SERIAL PRIMARY KEY, -- id
    comment_text TEXT, -- текст комментария 
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, -- время добавления комментарий 
    user_id INT REFERENCES names(id) -- связь с id из таблицы names
);

-- внесение данных в таблицу names
INSERT INTO names (id, name) VALUES (1, 'User1'), (2, 'User2'), (3, 'User3');

-- внесение данных в таблицу comments
INSERT INTO comments (id, comment_text, created_at, user_id) VALUES
    (1, 'Comment 1 by User1', '2024-05-08 08:00:00', 1),
    (2, 'Comment 2 by User1', '2024-05-08 08:10:00', 1),
    (3, 'Comment 3 by User1', '2024-05-08 08:20:00', 1),
    (4, 'Comment 4 by User1', '2024-05-08 08:20:00', 1),
    (5, 'Comment 5 by User1', '2024-05-08 08:20:00', 1),
    (6, 'Comment 6 by User1', '2024-05-08 08:20:00', 1),
    (7, 'Comment 7 by User1', '2024-05-08 08:20:00', 1),
    (8, 'Comment 1 by User2', '2024-05-08 08:30:00', 2),
    (9, 'Comment 2 by User2', '2024-05-08 08:40:00', 2),
    (10, 'Comment 3 by User2', '2024-05-08 08:40:00', 2)
    (11, 'Comment 4 by User2', '2024-05-08 08:40:00', 2)
    (12, 'Comment 5 by User2', '2024-05-08 08:40:00', 2)
    (13, 'Comment 1 by User3', '2024-05-08 09:00:00', 3),
    (14, 'Comment 2 by User3', '2024-05-08 09:00:00', 3),
    (15, 'Comment 3 by User3', '2024-05-08 09:00:00', 3);