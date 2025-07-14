import { writable, type Writable } from 'svelte/store';
import { setContext, getContext, onMount, onDestroy } from 'svelte';
import { listen } from '@tauri-apps/api/event';
import { invoke } from '@tauri-apps/api/core';

export interface Image {
	time: string;
	image: string;
}

type ImageStore = Writable<Image[]>;

const imagesStore: ImageStore = writable([]);

let unlisten: (() => void) | null = null;
let listenerStarted = false;

export function getImagesContext(): ImageStore {
	return getContext<ImageStore>('images');
}

export function startImageListener() {
	setContext<ImageStore>('images', imagesStore);

	if (listenerStarted) return;
	listenerStarted = true;

	onMount(() => {
		const setup = async () => {
			unlisten = await listen<Image>('images', (event) => {
				imagesStore.update((imgs) => {
					if (imgs.some((img) => img.time === event.payload.time)) return imgs;
					return [...imgs, event.payload];
				});
			});

			await invoke('take_images');
		};

		setup();
	});

	onDestroy(() => {
		if (unlisten) {
			unlisten();
			unlisten = null;
			listenerStarted = false;
		}
	});
}
