(define (domain truck)
	(:predicates
		(ROOM ?x) (BALL ?x) (GRIPPER ?x)
		(at-robby ?x) (at-ball ?x ?y)
		(free ?x) (carry ?x ?y))

    (:action move
    :parameters
        (?t - truck ?from ?to -location)
        :precondition
            (and (CONNECTED ?from ?to)
                (truck-at ?t ?from))
        effect:
            (and (not truck-at ?t ?from))
            (truck-at ?t ?to)))
)