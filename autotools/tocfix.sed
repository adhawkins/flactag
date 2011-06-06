/^FILE/{
	N
	/\n.*^START/p
	/\n.*START/! {
		s/\(.*\)\n\(.*\)/\1\nSTART 00:00:00\n\2/
	}
}