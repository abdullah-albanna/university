<script lang="ts">
	import * as Card from '$lib/components/ui/card/index.js';

	let { time, image }: { time: string; image: string } = $props();
</script>

<Card.Root
	class="mx-auto w-full max-w-md overflow-hidden rounded-2xl border shadow-lg transition-shadow hover:shadow-2xl"
>
	<Card.Header class="border-b  bg-gradient-to-r px-5 py-4">
		<Card.Title class="truncate text-lg font-semibold ">{time}</Card.Title>
	</Card.Header>

	<Card.Content class="p-0">
		<div class="relative aspect-[16/9] w-full overflow-hidden">
			<img
				src={'data:image/png;base64,' + image}
				alt="Captured image"
				class="h-full w-full object-cover transition-transform duration-300 hover:scale-105"
			/>
			<!-- Optional image overlay, could use it for metadata -->
			<!--
			<div class="absolute bottom-2 right-2 bg-white/70 backdrop-blur px-2 py-1 text-xs text-gray-700 rounded">
				Image metadata here
			</div>
			-->
		</div>
	</Card.Content>

	<!-- Footer -->
	<div class="flex items-center justify-between border-t px-5 py-3 text-sm">
		<span class="italic">Captured</span>
		<span>🕒 {time}</span>
	</div>
</Card.Root>
