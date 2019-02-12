import hashlib

hashf = lambda *args: hashlib.sha256(''.join([str(arg) for arg in args]).encode()).hexdigest()
input_data = "some_random_input_data"
salt = 'some_random_salt'

def balloon(input_data, salt):
	space_cost = 16
	time_cost = 20
	delta = 3
	cnt = 0

	# Step 1. Expand input into buffer
	buf = [hashf(cnt, input_data, salt)]
	cnt += 1

	for m in range(1, space_cost):
		buf.append(hashf(cnt, buf[m - 1]))
		cnt += 1

	# Step 2. Mix buffer contents
	for t in range(time_cost):
		for m in range(space_cost):
			# Step 2a. Hash last and current blocks
			buf[m] = hashf(cnt, buf[(m - 1) % space_cost], buf[m])
			cnt += 1

			for i in range(delta):
				# Step 2b. Hash in pseudorandomly chosen blocks
				other = int(hashf(cnt, salt, t, m, i), 16) % space_cost
				cnt += 1
				buf[m] = hashf(cnt, buf[m], buf[other])
				cnt += 1

	# Step 3. Extract output from buffer
	return buf[-1]

print(balloon(input_data, salt))
