(define (problem truck) 
(:domain truck)
(:objects
    city1 city2 city3
    truck1
)

(:init
    (truck-at city1)
    (CONNECTED city1 city1)
    (CONNECTED city1 city2)
    (CONNECTED city1 city3)
    (CONNECTED city2 city1)
    (CONNECTED city2 city2)
    (CONNECTED city3 city3)
    (CONNECTED city3 city1)
    (truck-at city1)
)

(:goal 
    (truck-at city3)
)

)
