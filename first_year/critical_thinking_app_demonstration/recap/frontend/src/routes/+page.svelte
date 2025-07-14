<script lang="ts">
	import TermsCard from '$lib/components/terms_card.svelte';
	import { getImagesContext, startImageListener } from '$lib/images_context';
	import ImageCard from '$lib/components/screenshot_card.svelte';

	let accepted = $state(false);

	function setAccepted(): void {
		accepted = true;
	}

	let images = $derived.by(() => {
		if (accepted) {
			startImageListener();

			return getImagesContext();
		} else {
			return null;
		}
	});
</script>

{#if accepted}
	{#if images}
		<div
			class="flex max-w-full auto-cols-max grid-flow-col grid-rows-6 flex-wrap items-center justify-center gap-6 overflow-auto p-4"
		>
			{#each $images as img}
				<ImageCard time={img.time} image={img.image} />
			{/each}
		</div>
	{/if}
{:else}
	<div class="flex h-screen w-full items-center justify-center px-4">
		<TermsCard {setAccepted}></TermsCard>
	</div>
{/if}
