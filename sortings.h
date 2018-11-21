static int64_t comps_count = 0;
static int64_t swap_count = 0;

void resetCounters() {
	comps_count = 0, swap_count = 0;
}


template <typename t>
t* selsort(const t* input, size_t size) {
	t* result = copyArray(input, size);
	resetCounters();
	size_t i, j;
	int32_t min_index;
	for (i = 0; i < size - 1; i++) {
		min_index = i;
		for (j = i + 1; j < size; j++) {
			comps_count++;
			if (result[j] < result[min_index]) {
				min_index = j;
			}
		}
		swap(result[min_index], result[i]);
	}
	return result;
}

template <typename t>
t* swapsort(const t* input, size_t size) {
	t* result = copyArray(input, size);
	resetCounters();
	for (size_t i = 0; i < size - 1; i++) {
		for (size_t j = i + 1; j < size; j++) {
			comps_count++;
			if (result[i] > result[j]) {
				swap(result[i], result[j]);
			}
		}
	}
	return result;
}

template <typename t>
t* shellsort(const t* input, size_t size) {
	t* result = copyArray(input, size);
	resetCounters();
	t i, j, step, tmp;
	for (step = size / 2; step > 0; step /= 2)
		for (i = step; i < size; i++)
		{
			tmp = result[i];
			for (j = i; j >= step; j -= step)
			{
				comps_count++;
				if (tmp < result[j - step])
					result[j] = result[j - step];
				else {
					break;
				}
			}
			result[j] = tmp;
		}
	return result;
}

template <typename t>
t split(t* arr, size_t left, size_t right) {
	t pivot = left;
	for (int i = left + 1; i < right; i++) {
		comps_count++;
		if (arr[i] < arr[pivot]) {
			if (pivot + 1 != i) {
				std::swap(arr[pivot], arr[pivot + 1]);
			}
			std::swap(arr[pivot], arr[i]);
			pivot++;
		}
	}
	return pivot;
}

template <typename t>
t* quicksort(t* input, size_t left, size_t right, t* result, bool first_run = true) {
	if (first_run) {
		result = copyArray(input, right);
		resetCounters();
		first_run = false;
	}
	if (right - left < 2) {
		return result;
	}
	else {
		int pivot = split(result, left, right);
		quicksort(result, left, pivot, result, first_run);
		quicksort(result, pivot + 1, right, result, first_run);
	}
	return result;
}


template <typename t>
t* swapsort_1(const t* input, size_t size) {
	t* result = copyArray(input, size);
	bool made_swap;
	for (size_t i = 0; i < size - 1; i++) {
		made_swap = false;
		for (size_t j = 0; j < size - 1; j++) {
			comps_count++;
			if (result[j] > result[j + 1]) {
				swap(result[j], result[j + 1]);
				made_swap = true;
			}
		}
		if (!made_swap) {
			break;
		}
	}
	return result;
}

template <typename t>
t* swapsort_2(const t* input, size_t size) {
	t* result = copyArray(input, size);
	resetCounters();
	size_t last_index = size;
	size_t j;
	for (size_t i = 0; i < size - 1; i++) {
		for (j = 0; j < size - i - 1; j++) {
			comps_count++;
			if (result[j] > result[j + 1]) {
				swap(result[j], result[j + 1]);
				last_index = j;
			}
		}
	}
	return result;
}

template <typename t>
t* insertionsort(const t* input, size_t size) {
	t* result = copyArray(input, size);
	resetCounters();
	size_t key, j;
	for (size_t i = 1; i < size; i++)
	{
		key = result[i];
		j = i - 1;
		comps_count += 2;
		while (j >= 0 && result[j] > key) {
			comps_count += 2;
			result[j + 1] = result[j];
			j = j - 1;
		}
		result[j + 1] = key;
	}
	return result;
}

template <typename t>
void heapify(t* input, size_t n, size_t i) {
	int32_t largest = i;
	int32_t l = 2 * i + 1;
	int32_t r = 2 * i + 2;

	comps_count++;
	if (l < n && input[l] > input[largest]) {
		largest = l;
	}
	comps_count++;
	if (r < n && input[r] > input[largest]) {
		largest = r;
	}
	if (largest != i)
	{
		swap(input[i], input[largest]);
		heapify(input, n, largest);
	}
}

template <typename t>
t* heapSort(const t* input, size_t n, t* result, bool first_run = true) {
	if (first_run) {
		result = copyArray(input, n);
		resetCounters();
		first_run = false;
	}
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(result, n, i);

	for (int i = n - 1; i >= 0; i--)
	{
		swap(result[0], result[i]);

		heapify(result, i, 0);
	}
	return result;
}